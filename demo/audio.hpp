#pragma once
#include "typecontrol.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>

namespace flat
{
    struct Audio
    {
        virtual ~Audio() {}
    };

    enum class AudioAttribType
    {
        positionX,
        positionY,
        positionZ,
        velocityX,
        velocityY,
        velocityZ,
        looping,
        gain,
    };

    class AudioAttrib
    {
    private:
        AudioAttribType type;
        float val;

    public:
        AudioAttrib(AudioAttribType t, float f) : type(t), val(f) {}
        ~AudioAttrib() {}
        AudioAttribType getType() { return type; }
        float getVal() { return val; }
    };

    struct AudioSource
    {
    private:
        Audio* currentAudio;

    public:
        AudioSource() : currentAudio(nullptr) {}
        virtual ~AudioSource() {}

        AudioSource& operator()(Audio& audio)
        {
            currentAudio = &audio;
            return *this;
        }

        virtual std::function<void(float)> operator[](flat::AudioAttribType type) = 0;

        Audio& getCurrentAudio() { return *currentAudio; }
    };

    class StopFlag
    {
    private:
        AudioSource* source;

    public:
        StopFlag(AudioSource& s) : source(&s) {}
        ~StopFlag() {}
        AudioSource& getAudioSource()
        {
            if(!source)
            {
                std::cerr << "error: null audio source in StopFlag" << std::endl;
                abort();
            }

            return *source;
        }
    };

    class ResumeFlag
    {
    private:
        AudioSource* source;

    public:
        ResumeFlag(AudioSource& s) : source(&s) {}
        ~ResumeFlag() {}
        AudioSource& getAudioSource()
        {
            if(!source)
            {
                std::cerr << "error: null audio source in ResumeFlag" << std::endl;
                abort();
            }

            return *source;
        }
    };

    template <typename T>
    concept AudioMixerAttribArgs = flat::is_same<T, AudioAttrib, AudioSource,StopFlag,ResumeFlag>();

    template <typename T> struct AudioMixer
    {
        template <typename U>
        AudioMixer& operator<<(U&& u)
            requires(AudioMixerAttribArgs<U>)
        {
            using UType = std::remove_cvref_t<U>;
            if constexpr(std::is_same<UType, AudioAttrib>())
                static_cast<T*>(this)->imp_setAttrib(u);
            else if constexpr(std::is_same<UType, AudioSource>())
                static_cast<T*>(this)->imp_playAudioFromSource(u);
            else if constexpr(std::is_same<UType,StopFlag>())
                static_cast<T*>(this)->imp_stopAudioSource(u);
            else if constexpr(std::is_same<UType,ResumeFlag>())
                static_cast<T*>(this)->imp_resumeAudioSource(u);

            return *this;
        }

        std::unique_ptr<AudioSource> genAudioSource() { return static_cast<T*>(this)->imp_genAudioSource(); }
        std::unique_ptr<Audio> genAudio(std::string_view path) { return static_cast<T*>(this)->imp_genAudio(path); }
    };
}  // namespace audapi