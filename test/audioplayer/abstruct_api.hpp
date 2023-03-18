#pragma once
#include "static_type_check.hpp"
#include <iostream>
#include <memory>
#include <string_view>
#include <type_traits>

namespace audapi
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

        virtual void setAttrib(AudioAttrib attri) = 0;

        Audio& getCurrentAudio() { return *currentAudio; }
    };

    template <typename T>
    concept AudioMixerAttribArgs = stool::same_type<T, AudioAttrib, AudioSource>();

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

            return *this;
        }

        std::unique_ptr<AudioSource> genAudioSource() { return static_cast<T*>(this)->imp_genAudioSource(); }
        std::unique_ptr<Audio> genAudio(std::string_view path) { return static_cast<T*>(this)->imp_genAudio(path); }
    };
}  // namespace audapi