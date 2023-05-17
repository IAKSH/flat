#pragma once

#include "OpenAL/openal_buffer.hpp"
#include "OpenAL/openal_source.hpp"
#include "OpenAL/openal_scope.hpp"
#include <memory>

namespace flat
{
    class Object
    {
    private:
        inline static unsigned long long object_count = 0;
        long long id;

    protected:
        void generate_id();

    public:
        virtual ~Object() = default;
        long long get_id() const;
    };

    class Sound : public Object
    {
    private:
        openal::Buffer<openal::Format::MONO16> buffer;

    public:
        Sound(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Sound();
        void play();
        void pause();
        void resume();
        void restart();
    };

    class Music : public Object
    {
    private:
        openal::Buffer<openal::Format::STEREO16> buffer;

    public:
        Music(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Music();
        void play();
        void pause();
        void resume();
        void restart();
    };

    class Sample : public Object
    {
    private:
        std::unique_ptr<unsigned char[]> pcm_data;
        size_t pcm_len;
        int channels;
        int sample_rate;
        int byte_rate;
        int bits_per_sample;

    public:
        Sample(std::unique_ptr<unsigned char[]> pcm,size_t pcm_len,int channels,int sample_rate,int byte_rate,int bits_per_sample);
        ~Sample();
        std::unique_ptr<Sound> gen_sound();
        std::unique_ptr<Music> gen_music();
    };

    class Frame : public Object
    {
    private:

    public:
        Frame();
        ~Frame();

        void flush();
    };

    // Texture --(RenderPipe)--> Frame
    // Frame.get_texture() --(RenderPipe)--> new Frame
    // Frame.flush_to_screen(): display on screen using default shader
    class Texture : public Object
    {
    private:

    public:
        Texture();
        ~Texture();

        void flush();
    };

    class CharTexture : public Texture
    {

    };

    class Image : public Object
    {
    private:
        std::unique_ptr<unsigned char[]> bitmap_data;
        int width;
        int height;

    public:
        Image(std::unique_ptr<unsigned char[]> data,int w,int h);
        ~Image();
        std::unique_ptr<Texture> gen_texture();
    };

    // TODO
    class Font : public Object
    {
    private:

    public:
        Font();
        ~Font();
    };
}