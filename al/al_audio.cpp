#include "al_audio.hpp"
#include "AL/al.h"
#include "AL/alc.h"
#include <iostream>
#include <process.h>

/*
    flat::al::Listener
*/

flat::al::Listener::Listener()
    :device(nullptr),context(nullptr)
{
}

flat::al::Listener::~Listener()
{
    releaseOpenAL();
}

void flat::al::Listener::releaseOpenAL()
{
    if(context)
        alcDestroyContext(context);
    if(device)
        alcCloseDevice(device);
}

void flat::al::Listener::initAudioListner()
{
    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device,nullptr);
    alcMakeContextCurrent(context);

    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
        std::cerr << "OpenAL error: " << alGetString(error) << std::endl;
}

void flat::al::Listener::setAudioListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION,x,y,z);
}

void flat::al::Listener::addAudioListenerPosition(float x, float y, float z)
{
    float _x = getAudioListenerPosX() + x;
    float _y = getAudioListenerPosY() + y;
    float _z = getAudioListenerPosZ() + z;
    alListener3f(AL_POSITION,_x,_y,_z);
}

float const flat::al::Listener::getAudioListenerPosX()
{
    float buffer;
    alGetListener3f(AL_POSITION,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::al::Listener::getAudioListenerPosY()
{
    float buffer;
    alGetListener3f(AL_POSITION,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::al::Listener::getAudioListenerPosZ()
{
    float buffer;
    alGetListener3f(AL_POSITION,nullptr,nullptr,&buffer);
    return buffer;
}

void flat::al::Listener::setAudioListenerVelocity(float x, float y, float z)
{
    alListener3f(AL_VELOCITY,x,y,z);
}

void flat::al::Listener::addAudioListenerVelocity(float x, float y, float z)
{
    float _x = getAudioListenerPosX() + x;
    float _y = getAudioListenerPosY() + y;
    float _z = getAudioListenerPosZ() + z;
    alListener3f(AL_VELOCITY,_x,_y,_z);
}

float const flat::al::Listener::getAudioListenerVelX()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::al::Listener::getAudioListenerVelY()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::al::Listener::getAudioListenerVelZ()
{
    float buffer;
    alGetListener3f(AL_VELOCITY,nullptr,nullptr,&buffer);
    return buffer;
}

void flat::al::Listener::setAudioListenerGain(float gain)
{
    alListenerf(AL_GAIN,gain);
}

void flat::al::Listener::addAudioListenerGain(float gain)
{
    float buffer;
    alGetListenerf(AL_GAIN,&buffer);
    alListenerf(AL_GAIN,buffer + gain);
}

float const flat::al::Listener::getAudioListenerGain()
{
    float buffer;
    alGetListenerf(AL_GAIN,&buffer);
    return buffer;
}

/*
    flat::al::Source
*/

flat::al::Source::Source()
    : sourceId(0),sampleOffset(0)
{
}

flat::al::Source::~Source()
{
    releaseSource();
} 

void flat::al::Source::releaseSource()
{
    alDeleteSources(1,&sourceId);
}

void flat::al::Source::checkSource()
{
    if(!sourceId)
    {
        std::cerr << "error: openal audio source use without initialize" << std::endl;
        abort();
    }
}

void flat::al::Source::initAudioSource()
{
    alGenSources(1,&sourceId);
}

void flat::al::Source::setAudioSourcePosition(float x, float y, float z)
{
    checkSource();
    alSource3f(sourceId,AL_POSITION,x,y,z);
}

void flat::al::Source::addAudioSourcePosition(float x, float y, float z)
{
    checkSource();
    float _x = getAudioSourcePosX() + x;
    float _y = getAudioSourcePosY() + y;
    float _z = getAudioSourcePosZ() + z;
    alSource3f(sourceId,AL_POSITION,_x,_y,_z);
}

float const flat::al::Source::getAudioSourcePosX()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_POSITION,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::al::Source::getAudioSourcePosY()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_POSITION,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::al::Source::getAudioSourcePosZ()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_POSITION,nullptr,nullptr,&buffer);
    return buffer;
}

void flat::al::Source::setAudioSourceVelocity(float x, float y, float z)
{
    checkSource();
    alSource3f(sourceId,AL_VELOCITY,x,y,z);
}

void flat::al::Source::addAudioSourceVelocity(float x, float y, float z)
{
    checkSource();
    float _x = getAudioSourceVelX() + x;
    float _y = getAudioSourceVelY() + y;
    float _z = getAudioSourceVelZ() + z;
    alSource3f(sourceId,AL_VELOCITY,_x,_y,_z);
}

float const flat::al::Source::getAudioSourceVelX()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_VELOCITY,&buffer,nullptr,nullptr);
    return buffer;
}

float const flat::al::Source::getAudioSourceVelY()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_VELOCITY,nullptr,&buffer,nullptr);
    return buffer;
}

float const flat::al::Source::getAudioSourceVelZ()
{
    checkSource();
    float buffer;
    alGetSource3f(sourceId,AL_VELOCITY,nullptr,nullptr,&buffer);
    return buffer;
}

void flat::al::Source::setAudioSourceGain(float gain)
{
    checkSource();
    alSourcef(sourceId,AL_GAIN,gain);
}

void flat::al::Source::addAudioSourceGain(float gain)
{
    checkSource();
    float buffer;
    alGetSourcef(sourceId,AL_GAIN,&buffer);
    alSourcef(sourceId,AL_GAIN,buffer + gain);
}

float const flat::al::Source::getAudioSourceGain()
{
    checkSource();
    float buffer;
    alGetSourcef(sourceId,AL_GAIN,&buffer);
    return buffer;
}

void flat::al::Source::setAudioSourceLooping(bool looping)
{
    checkSource();
    alSourcei(sourceId,AL_LOOPING,looping);
}

bool const flat::al::Source::getAudioSourceLooping()
{
    checkSource();
    bool buffer;
    alGetSourcei(sourceId,AL_LOOPING,(ALint*)(&buffer));
    return buffer;
}

void flat::al::Source::playAudio(uint32_t id)
{
    checkSource();
    alSourcei(sourceId,AL_BUFFER,id);
    alSourcePlay(sourceId);
}

void flat::al::Source::pauseAudio()
{
    checkSource();
    alSourcePause(sourceId);
    alGetSourcei(sourceId, AL_SAMPLE_OFFSET, &sampleOffset);
}

void flat::al::Source::resumeAudio()
{
    checkSource();
    alSourcePlay(sourceId);
    alSourcei(sourceId, AL_SAMPLE_OFFSET, sampleOffset);
}


