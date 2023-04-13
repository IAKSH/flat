#pragma once

#include "mass_point.hpp"

#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils
{
    class AudioSource
    {
    private:
        ALuint sourceID;
        void initialize();
        void release();

    public:
        AudioSource();
        AudioSource(AudioSource&) = delete;
        ~AudioSource();
        const ALuint& getSourceID() { return sourceID; }
    };
}