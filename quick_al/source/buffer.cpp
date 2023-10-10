#include <format>
#include <stdexcept>
#include <quick_al/buffer.hpp>

quick3d::al::Buffer::Buffer() noexcept
{
    generate_buffer();
}

quick3d::al::Buffer::Buffer(const Sample& sample) noexcept
{
    generate_buffer();
    write_to_buffer(sample);
}

quick3d::al::Buffer::Buffer(ALenum format,ALvoid* data,ALsizei size,ALsizei freq) noexcept
{
    generate_buffer();
    write_to_buffer(format, data, size, freq);
}

quick3d::al::Buffer::Buffer(short channels, short bps, ALvoid* data, ALsizei size, ALsizei freq) noexcept
{
    generate_buffer();
    write_to_buffer(channels, bps, data, size, freq);
}

quick3d::al::Buffer::~Buffer() noexcept
{
    delete_buffer();
}

ALuint quick3d::al::Buffer::get_buffer_id() const noexcept
{
    return buffer_id;
}

void quick3d::al::Buffer::write_to_buffer(const Sample& sample) noexcept
{
    const auto& codec{ sample.get_codec() };
    alBufferData(buffer_id,
        to_al_format(codec.get_sample_channels(),codec.get_sample_bps()),
        codec.get_sample_pcm(),
        codec.get_sample_size(),
        codec.get_sample_freq());
}

void quick3d::al::Buffer::write_to_buffer(ALenum format, ALvoid* data, ALsizei size, ALsizei freq) noexcept
{
    alBufferData(buffer_id, format, data, size, freq);
}

void quick3d::al::Buffer::write_to_buffer(short channels, short bps, ALvoid* data, ALsizei size, ALsizei freq) noexcept
{
    alBufferData(buffer_id, to_al_format(channels, bps), data, size, freq);
}

ALenum quick3d::al::Buffer::to_al_format(short channels, short bps) noexcept(false)
{
    bool stereo = channels > 1;
    switch (bps)
    {
    case 16:
        if (stereo)
            return AL_FORMAT_STEREO16;
        else
            return AL_FORMAT_MONO16;
    case 8:
        if (stereo)
            return AL_FORMAT_STEREO8;
        else
            return AL_FORMAT_MONO8;
    default:
        throw std::runtime_error(std::format("cant find OpenAL format where channels={}, samples={}", channels, bps));
    }
}

void quick3d::al::Buffer::generate_buffer() noexcept
{
    alGenBuffers(1, &buffer_id);
}

void quick3d::al::Buffer::delete_buffer() noexcept
{
    alDeleteBuffers(1, &buffer_id);
}
