#pragma once

#include <cstdint>

namespace flat
{
    struct AudioListener
    {
        virtual ~AudioListener() {}
        virtual void initAudioListner() = 0;
        virtual void setAudioListenerPosition(float x,float y,float z) = 0;
        virtual void addAudioListenerPosition(float x,float y,float z) = 0;
        virtual float const getAudioListenerPosX() = 0;
        virtual float const getAudioListenerPosY() = 0;
        virtual float const getAudioListenerPosZ() = 0;
        virtual void setAudioListenerVelocity(float x,float y,float z) = 0;
        virtual void addAudioListenerVelocity(float x,float y,float z) = 0;
        virtual float const getAudioListenerVelX() = 0;
        virtual float const getAudioListenerVelY() = 0;
        virtual float const getAudioListenerVelZ() = 0;
        virtual void setAudioListenerGain(float gain) = 0;
        virtual void addAudioListenerGain(float gain) = 0;
        virtual float const getAudioListenerGain() = 0;
    };

    struct AudioSource
    {
        virtual ~AudioSource() {}
        virtual void initAudioSource() = 0;
        virtual void setAudioSourcePosition(float x,float y,float z) = 0;
        virtual void addAudioSourcePosition(float x,float y,float z) = 0;
        virtual float const getAudioSourcePosX() = 0;
        virtual float const getAudioSourcePosY() = 0;
        virtual float const getAudioSourcePosZ() = 0;
        virtual void setAudioSourceVelocity(float x,float y,float z) = 0;
        virtual void addAudioSourceVelocity(float x,float y,float z) = 0;
        virtual float const getAudioSourceVelX() = 0;
        virtual float const getAudioSourceVelY() = 0;
        virtual float const getAudioSourceVelZ() = 0;
        virtual void setAudioSourceGain(float gain) = 0;
        virtual void addAudioSourceGain(float gain) = 0;
        virtual float const getAudioSourceGain() = 0;
        virtual void setAudioSourceLooping(bool looping) = 0;
        virtual bool const getAudioSourceLooping() = 0;
        virtual void playAudio(uint32_t id) = 0;
        virtual void pauseAudio() = 0;
        virtual void resumeAudio() = 0;
    };

    struct Audio
    {
        virtual ~Audio() {}
        virtual void loadAudioFromFile(const char* path) = 0;
        virtual uint32_t getAudioId() = 0;
    };
}