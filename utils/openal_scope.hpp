#pragma once

#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils::openal
{
    // OpenAL state manager based on RAII
    class Scope
    {
    private:
        ALCcontext* context;

    public:
        Scope()
        {
            context = alcGetCurrentContext();
            alcSuspendContext(context);
        }
        ~Scope()
        {
            alcProcessContext(context);
        }
    };
}