#pragma once

#include "../core/loggers.hpp"
#include <AL/al.h>
#include <AL/alc.h>

namespace ni::utils::openal
{
    enum class PCMFormat
    {
        MONO8,MONO16,STEREO8,STEREO16
    };

    template <PCMFormat format>
    class Buffer
    {
    private:
        ALuint bufferID;

    public:
        Buffer(const unsigned char* pcm,int sampleRate,size_t len)
        {
            ALenum formatEnum;
            if constexpr(format == PCMFormat::MONO8)
                formatEnum = AL_FORMAT_MONO8;
            else if constexpr(format == PCMFormat::MONO16)
                formatEnum = AL_FORMAT_MONO16;
            else if constexpr(format == PCMFormat::STEREO8)
                formatEnum = AL_FORMAT_STEREO8;
            else if constexpr(format == PCMFormat::STEREO16)
                formatEnum = AL_FORMAT_STEREO16;

            alGenBuffers(1,&bufferID);
            alBufferData(bufferID,formatEnum,pcm,len,sampleRate);
        }

        ~Buffer() {alDeleteBuffers(1,&bufferID);}
        const ALuint& getBufferID() {return bufferID;}
    };
}