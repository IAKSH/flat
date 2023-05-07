#pragma once

#include "../core/loggers.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils::openal
{
    class Source : public core::DisableCopy
    {
    private:
        ALuint sourceID;
    
    public:
        Source();
        ~Source();
        const ALuint& getSourceID() {return sourceID;}
    };
}