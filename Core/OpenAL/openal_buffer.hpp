#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <cstdlib>

namespace flat::openal
{
    enum class Format
    {
        MONO8,MONO16,STEREO8,STEREO16
    };

    template <Format format>
    class Buffer
    {
    private:
        ALuint buffer_id;

    public:
        Buffer(const unsigned char* pcm,int sample_rate,size_t len)
        {
            ALenum format_enum;
            if constexpr(format == Format::MONO8)
                format_enum = AL_FORMAT_MONO8;
            else if constexpr(format == Format::MONO16)
                format_enum = AL_FORMAT_MONO16;
            else if constexpr(format == Format::STEREO8)
                format_enum = AL_FORMAT_STEREO8;
            else if constexpr(format == Format::STEREO16)
                format_enum = AL_FORMAT_STEREO16;
            
            alGenBuffers(1,&buffer_id);
            alBufferData(buffer_id,format_enum,pcm,len,sample_rate);
        }

        ~Buffer()
        {
            alDeleteBuffers(1,&buffer_id);
        }

        ALuint get_buffer_id()
        {
            return buffer_id;
        }
    };
}