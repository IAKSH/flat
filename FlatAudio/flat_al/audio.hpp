#pragma once

#include "../audio.hpp"

#include <filesystem>

#include <AL/al.h>
#include <AL/alc.h>

namespace flat::al
{
    class Listener : public flat::AudioListener
    {
    private:
        ALCdevice* device;
        ALCcontext* context;
        void releaseOpenAL();

    public:
        Listener();
        virtual ~Listener() override;
        virtual void initAudioListner() override;
        virtual void setAudioListenerPosition(float x,float y,float z) override;
        virtual void addAudioListenerPosition(float x,float y,float z) override;
        virtual float const getAudioListenerPosX() override;
        virtual float const getAudioListenerPosY() override;
        virtual float const getAudioListenerPosZ() override;
        virtual void setAudioListenerVelocity(float x,float y,float z) override;
        virtual void addAudioListenerVelocity(float x,float y,float z) override;
        virtual float const getAudioListenerVelX() override;
        virtual float const getAudioListenerVelY() override;
        virtual float const getAudioListenerVelZ() override;
        virtual void setAudioListenerGain(float gain) override;
        virtual void addAudioListenerGain(float gain) override;
        virtual float const getAudioListenerGain() override;
    };

    class Source : public flat::AudioSource
    {
    private:
        uint32_t sourceId;
        int sampleOffset;
        void releaseSource();
        void checkSource();

    public:
        Source();
        virtual ~Source() override;
        virtual void initAudioSource() override;
        virtual void setAudioSourcePosition(float x,float y,float z) override;
        virtual void addAudioSourcePosition(float x,float y,float z) override;
        virtual float const getAudioSourcePosX() override;
        virtual float const getAudioSourcePosY() override;
        virtual float const getAudioSourcePosZ() override;
        virtual void setAudioSourceVelocity(float x,float y,float z) override;
        virtual void addAudioSourceVelocity(float x,float y,float z) override;
        virtual float const getAudioSourceVelX() override;
        virtual float const getAudioSourceVelY() override;
        virtual float const getAudioSourceVelZ() override;
        virtual void setAudioSourceGain(float gain) override;
        virtual void addAudioSourceGain(float gain) override;
        virtual float const getAudioSourceGain() override;
        virtual void setAudioSourceLooping(bool looping) override;
        virtual bool const getAudioSourceLooping() override;
        virtual void playAudio(uint32_t id) override;
        virtual void pauseAudio() override;
        virtual void resumeAudio() override;
    };

    class Audio : public flat::Audio
    {
    private:
        uint32_t bufferId;
        void releaseAudio();
        void checkBuffer();

    public:
        Audio();
        virtual ~Audio();
        virtual void loadAudioFromFile(const char* path) override;
        virtual uint32_t getAudioId() override;
    };
}