#pragma once

#include "../../misc/disable_copy.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace flat::openal
{
    class Source : misc::DisableCopy
    {
    private:
        ALuint source_id;

    public:
        Source();
        ~Source();
        ALuint get_source_id() {return source_id;}
    };
}