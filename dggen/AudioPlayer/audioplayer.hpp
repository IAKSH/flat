#pragma once

#include <string_view>

// abstruct layer of AudioPlayer

namespace dggen
{
    enum class AudioPlayerAttri
    {
        position,velocity,gain,pitch,looping
    };

    // abstruct API collection
    struct AudioSource
    {
        /*
        virtual ~AudioSource() {}
        virtual void genAudio(std::string_view name,std::string_view path) = 0;
        virtual void releaseAudio(std::string_view name) = 0;
        virtual void genAudioSource(std::string_view name) = 0;
        virtual void releaseAudioSource(std::string_view name) = 0;
        virtual void playAudioFromSource(std::string_view audioName,std::string_view sourceName) = 0;
        virtual void setAudioSourceAtrri(std::string_view name,AudioPlayerAttri attri,float val) = 0;
        virtual void stopSource(std::string_view name) = 0;
        virtual void resumeSource(std::string_view name) = 0;
        virtual void setGlobalAttri(AudioPlayerAttri attri,float val) = 0;
        virtual float const getGlobalAttri(AudioPlayerAttri attri) = 0;
        virtual float const getAudioSourceAttri(std::string_view name,AudioPlayerAttri attri) = 0;
        */
    };
}