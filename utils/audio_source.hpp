#pragma once

#include "mass_point.hpp"

#include <al/al.h>
#include <al/alc.h>

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