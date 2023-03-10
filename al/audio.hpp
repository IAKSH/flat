#pragma once

#include <iostream>
#include <filesystem>

namespace flat
{
    struct Audio
    {
        virtual void loadAudioFromFile(std::filesystem::path path) = 0;
        virtual void releaseAudio() = 0;
        virtual uint32_t const getAudioBufferId() = 0;
    };

    struct AudioSource
    {
        virtual void initAudioSource() = 0;
        virtual void releaseAudioSource() = 0;
        virtual void pauseAudio() = 0;
        virtual void resumeAudio() = 0;
        virtual void playAudio(uint32_t bufferId) = 0;
        virtual void setAudioSourcePosition(float x,float y,float z) = 0;
        virtual void setAudioSourceVelocity(float x,float y,float z) = 0;
        virtual void addAudioSourcePosition(float x,float y,float z) = 0;
        virtual void addAudioSourceVelocity(float x,float y,float z) = 0;
        virtual void setAudioSourceVolume(float v) = 0;
        virtual void setAudioSourceLooping(bool b) = 0;
        virtual bool const getAudioSourceLooping() = 0;
        virtual float const getAudioSourcePosX() = 0;
        virtual float const getAudioSourcePosY() = 0;
        virtual float const getAudioSourcePosZ() = 0;
        virtual float const getAudioSourceVelX() = 0;
        virtual float const getAudioSourceVelY() = 0;
        virtual float const getAudioSourceVelZ() = 0;
        virtual float const getAudioSourceVolume() = 0;
    };

    struct AudioListener
    {
        virtual void initAudioListener() = 0;
        virtual void releaseAudioListener()= 0;
        virtual void setAudioListenerPosition(float x,float y,float z) = 0;
        virtual void setAudioListenerVelocity(float x,float y,float z) = 0;
        virtual void addAudioListenerPosition(float x,float y,float z) = 0;
        virtual void addAudioListenerVelocity(float x,float y,float z) = 0;
        virtual void setAudioListenerVolume(float v) = 0;
        virtual float const getAudioListenerPosX() = 0;
        virtual float const getAudioListenerPosY() = 0;
        virtual float const getAudioListenerPosZ() = 0;
        virtual float const getAudioListenerVelX() = 0;
        virtual float const getAudioListenerVelY() = 0;
        virtual float const getAudioListenerVelZ() = 0;
        virtual float const getAudioListenerVolume() = 0;
    };
}