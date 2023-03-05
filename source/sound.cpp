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
    alBuffer3f(sourceId, AL_POSITION, getCentralPosX(), getCentralPosY(), 0.0f);
    alBuffer3f(sourceId, AL_VELOCITY, getCentralPosX(), getCentralPosY(), 0.0f);
}

void flat::SoundSource::setSoundVolume(float volume)
{
    alSourcef(sourceId, AL_GAIN, volume);
}

void flat::SoundSource::setSoundLoopable(bool loopable)
{
    alSourcei(sourceId, AL_LOOPING, loopable);
}

void flat::SoundSource::playSound(Audio& audio)
{
    //alSourcei(sourceId, AL_BUFFER, id);
    for(auto& item : audio.getBufferIds())
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

void flat::Listener::updateListener()
{
    alListener3f(AL_POSITION, getCentralPosX(), getCentralPosY(), 0.0f);
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
    std::ifstream file(path.data(), std::ios::binary);
    if (!file)
    {
        std::cerr << "[ERROR] Failed to open " << path << std::endl;
        abort();
    }

    mp3dec_t mp3dec;
    mp3dec_init(&mp3dec);
    mp3dec_frame_info_t info;

    std::vector<uint8_t> buffer(4096);

    while (true) {
        file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
        auto bytesRead = static_cast<size_t>(file.gcount());
        if (bytesRead == 0) {
            break;
        }

        // decode frame
        auto samplesDecoded = mp3dec_decode_frame(&mp3dec, buffer.data(), bytesRead, nullptr, &info);
        if (samplesDecoded > 0) {
            // get pcm (single frame)
            for (size_t i = 0; i < samplesDecoded; ++i) {
                auto pcmFrame = static_cast<int16_t>(buffer[i]);
                uint32_t bufferId;
                alGenBuffers(1,&bufferId);
                alBufferData(bufferId, AL_FORMAT_MONO16, &pcmFrame, samplesDecoded * sizeof(short), info.hz);
                bufferIds.push_back(bufferId);
            }
        }
    }
}

const std::vector<uint32_t>& flat::Audio::getBufferIds()
{
    return bufferIds;
}

void flat::Audio::releaseBuffer()
{
    for(auto& item : bufferIds)
        alDeleteBuffers(1,&item);
}