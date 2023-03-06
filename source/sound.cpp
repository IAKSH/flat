#include <vector>
#include <fstream>
#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

#include "sound.hpp"

flat::SoundSource::SoundSource()
{
}

flat::SoundSource::~SoundSource()
{
}

void flat::SoundSource::initializeSoundSource()
{
    alGenSources(1, &sourceId);
    alSourcef(sourceId, AL_PITCH, 1.0f);
    alSourcef(sourceId, AL_GAIN, 1.0f);
    alBuffer3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alBuffer3f(sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(sourceId, AL_LOOPING, false);
}

void flat::SoundSource::updateSoundSource()
{
    alBuffer3f(sourceId, AL_POSITION, getPosX(), getPosY(), 0.0f);
    alBuffer3f(sourceId, AL_VELOCITY, getPosX(), getPosY(), 0.0f);
}

void flat::SoundSource::setSoundVolume(float volume)
{
    alSourcef(sourceId, AL_GAIN, volume);
}

void flat::SoundSource::setSoundLoopable(bool loopable)
{
    alSourcei(sourceId, AL_LOOPING, loopable);
}

void flat::SoundSource::playSound(Audio &audio)
{
    alSourcei(sourceId, AL_BUFFER, audio.getBufferId());
    alSourcePlay(sourceId);
}

void flat::SoundSource::stopSound()
{
    alSourceStop(sourceId);
}

void flat::SoundSource::pauseSound()
{
    alSourcePause(sourceId);
    alGetSourcei(sourceId, AL_SAMPLE_OFFSET, &sampleOffset);
}

void flat::SoundSource::resumeSound()
{
    alSourcePlay(sourceId);
    alSourcei(sourceId, AL_SAMPLE_OFFSET, sampleOffset);
}

float flat::SoundSource::getSoundVolume()
{
    float volume;
    alGetSourcef(sourceId, AL_GAIN, &volume);
    return volume;
}

bool flat::SoundSource::getSoundLoopable()
{
    int loopable;
    alGetSourcei(sourceId, AL_LOOPING, &loopable);
    return static_cast<bool>(loopable);
}

flat::Listener::Listener()
{
}

flat::Listener::~Listener()
{
}

void flat::Listener::initializeListener()
{
    device = alcOpenDevice(NULL);
    if (!device)
    {
        std::cout << "[ERROR] Can't open OpenAL device" << std::endl;
        abort();
    }

    context = alcCreateContext(device, NULL);
    if (!context)
    {
        std::cout << "[ERROR] Can't create OpenAL context" << std::endl;
        // alcCloseDevice(device);
        abort();
    }

    alcMakeContextCurrent(context);
}

void flat::Listener::updateListener()
{
    alListener3f(AL_POSITION, getPosX(), getPosY(), 0.0f);
    alListener3f(AL_VELOCITY, getVelocityVec()[0], getVelocityVec()[1], 0.0f);
}

flat::Audio::Audio()
{
}

flat::Audio::~Audio()
{
    releaseBuffer();
}

void flat::Audio::load(std::string_view path)
{
    // read in the whole mp3 file
    std::ifstream ifs(path.data(), std::ios::binary);
    if (!ifs)
    {
        std::cerr << "[ERROR] Can't open " << path << std::endl;
        abort();
    }
    ifs.seekg(0, std::ios::end);
    std::streampos fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<uint8_t> mp3Binary(fileSize);
    ifs.read((char *)(mp3Binary.data()), fileSize);
    ifs.close();

    // decode with minimp3
    mp3dec_t mp3d;
    mp3dec_frame_info_t info;
    std::vector<short> allPCM;
    short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
    int readLength = 0;
    // decode frame by frame
    int samples = mp3dec_decode_frame(&mp3d, mp3Binary.data(), static_cast<int>(fileSize), pcm, &info);
    while (samples)
    {
        // collect pcm
        for (auto item : pcm)
            allPCM.push_back(item);
        readLength += info.frame_bytes;
        samples = mp3dec_decode_frame(&mp3d, mp3Binary.data() + readLength, static_cast<int>(fileSize) - readLength, pcm, &info);
    }

    // prepare OpenAL buffer
    alGenBuffers(1, &bufferId);
    ALenum format = (info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);
    alBufferData(bufferId, format, allPCM.data(), allPCM.size() * sizeof(short), info.hz);
}

const uint32_t &flat::Audio::getBufferId()
{
    return bufferId;
}

void flat::Audio::releaseBuffer()
{
    alDeleteBuffers(1, &bufferId);
}