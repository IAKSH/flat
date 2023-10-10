#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <quick_al/sample.hpp>

namespace quick3d::al
{
    class Buffer
    {
    private:
        ALuint buffer_id;

        void generate_buffer() noexcept;
        void delete_buffer() noexcept;
        ALenum to_al_format(short channels, short bps) noexcept(false);

    public:
        // this will create an empty buffer (without memory allocated in context)
        Buffer() noexcept;
        Buffer(const Sample& sample) noexcept;
        Buffer(ALenum format,ALvoid* data,ALsizei size,ALsizei freq) noexcept;
        Buffer(short channels,short bps,ALvoid* data,ALsizei size,ALsizei freq) noexcept;
        Buffer(Buffer&) = delete;
        ~Buffer() noexcept;

        ALuint get_buffer_id() const noexcept;
        void write_to_buffer(const Sample& sample) noexcept;
        void write_to_buffer(ALenum format,ALvoid* data,ALsizei size,ALsizei freq) noexcept;
        void write_to_buffer(short channels,short bps,ALvoid* data,ALsizei size,ALsizei freq) noexcept;
    };
}