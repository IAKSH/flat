#pragma once

#include "mass_point.hpp"
#include "template.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils
{
    class AudioSource : public DisableCopy
    {
    private:
        ALuint sourceID;
        void initialize();
        void release();

    public:
        AudioSource();
        ~AudioSource();
        const ALuint& getSourceID() { return sourceID; }
    };
}