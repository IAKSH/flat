#include "audio.hpp"

#include <AL/al.h>
#include <AL/alc.h>

#include "wavaudio.hpp"

namespace flat
{
    class Mp3Audio : public Audio
    {
    private:
        uint32_t alBufferId;
    public:
        Mp3Audio();
        ~Mp3Audio();
        void loadAudioFromFile(std::filesystem::path path) override;
        void releaseAudio() override;
        uint32_t const getAudioBufferId() override;
    };

    class WavAudio : public Audio
    {
    private:
        uint32_t alBufferId;
    public:
        WavAudio();
        ~WavAudio();
        void loadAudioFromFile(std::filesystem::path path) override;
        void releaseAudio() override;
        uint32_t const getAudioBufferId() override;
    };

    class ALAudioSource : public AudioSource
    {
    private:
        uint32_t alSourceId;
        int alSampleOffset;
    public:
        ALAudioSource();
        ~ALAudioSource();
        void initAudioSource() override;
        void releaseAudioSource() override;
        void pauseAudio() override;
        void resumeAudio() override;
        void playAudio(uint32_t bufferId) override;
        void setAudioSourcePosition(float x,float y,float z) override;
        void setAudioSourceVelocity(float x,float y,float z) override;
        void addAudioSourcePosition(float x,float y,float z) override;
        void addAudioSourceVelocity(float x,float y,float z) override;
        void setAudioSourceVolume(float v) override;
        void setAudioSourceLooping(bool b) override;
        bool const getAudioSourceLooping() override;
        float const getAudioSourcePosX() override;
        float const getAudioSourcePosY() override;
        float const getAudioSourcePosZ() override;
        float const getAudioSourceVelX() override;
        float const getAudioSourceVelY() override;
        float const getAudioSourceVelZ() override;
        float const getAudioSourceVolume() override;
    };

    class ALAudioListener : public AudioListener
    {
    private:
        ALCdevice *device;
		ALCcontext *context;

    public:
        ALAudioListener();
        ~ALAudioListener();
        void initAudioListener() override;
        void releaseAudioListener() override;
        void setAudioListenerPosition(float x,float y,float z) override;
        void setAudioListenerVelocity(float x,float y,float z) override;
        void addAudioListenerPosition(float x,float y,float z) override;
        void addAudioListenerVelocity(float x,float y,float z) override;
        void setAudioListenerVolume(float v) override;
        float const getAudioListenerPosX() override;
        float const getAudioListenerPosY() override;
        float const getAudioListenerPosZ() override;
        float const getAudioListenerVelX() override;
        float const getAudioListenerVelY() override;
        float const getAudioListenerVelZ() override;
        float const getAudioListenerVolume() override;
    };
}