#pragma once
#include "static_type_check.hpp"

namespace audapi
{
    struct Audio
    {

    };

    enum class AudioAtribType
    {
        positionX,positionY,positionZ,velocityX,velocityY,velocityZ,gain,
    };

    struct AudioAtrrib
    {

    };

    template <typename T>
    concept AudioSourceArgs = stool::same_type<T, Audio,AudioAtrrib>();

    template <typename T> struct AudioSource
    {
        template <typename U>
        AudioSource<T>& operator<<(U&& u)
            requires(AudioSourceArgs<U>)
        {
            if constexpr(std::is_same<U, Audio>())
                static_cast<T*>(this)->imp_playAudio(u);
            else if constexpr(std::is_same<U, AudioAtrrib>())
                static_cast<T*>(this)->imp_seAttrib(u);

            return *this;
        }
    };

    template <typename T,typename AudioSourceType>
    struct AudioMixer
    {
        AudioSource<AudioSourceType>& genAudioSource() {return static_cast<T*>(this)->imp_genAudioSource();}
    };
}  // namespace audapi