#include <vector>
#include <fstream>
#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>
extern "C"
{
#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>
}

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
    // alSourcei(sourceId, AL_BUFFER, id);
    for (auto &item : audio.getBufferIds())
        alSourceQueueBuffers(sourceId, 1, &item);
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
    // bad code
    // C file pointer for test
    FILE* fp = fopen(path.data(),"r");
    if (!fp)
    {
        std::cerr << "[ERROR] Failed to open " << path << std::endl;
        abort();
    }

    mp3dec_t mp3d;
    mp3dec_frame_info_t frame_info;
    ALenum format;
    int channels, rate, bps, size;
    unsigned char buffer[4096];
    short pcm[4096];

    mp3dec_init(&mp3d);

    while ((size = fread(buffer, 1, 4096, fp)) > 0)
    {
        int offset = 0;
        while (offset < size)
        {
            int samples = mp3dec_decode_frame(&mp3d, buffer + offset, size - offset, pcm, &frame_info);
            if (samples)
            {
                offset += frame_info.frame_bytes;
                if (!channels)
                {
                    channels = frame_info.channels;
                    rate = frame_info.hz;
                    bps = sizeof(short) * channels;
                    if (channels == 1)
                    {
                        format = AL_FORMAT_MONO16;
                    }
                    else
                    {
                        format = AL_FORMAT_STEREO16;
                    }
                }
                uint32_t bufferId;
                alGenBuffers(1,&bufferId);
                alBufferData(bufferId, format, pcm, samples * bps, rate);
                bufferIds.push_back(bufferId);
            }
            else
                break;
        }
    }
}

const std::vector<uint32_t> &flat::Audio::getBufferIds()
{
    return bufferIds;
}

void flat::Audio::releaseBuffer()
{
    for (auto &item : bufferIds)
        alDeleteBuffers(1, &item);
}