#pragma once

#include "OpenAL/openal_buffer.hpp"
#include "OpenAL/openal_source.hpp"
#include "OpenAL/openal_scope.hpp"
#include "OpenGL/opengl_texture.hpp"
#include "OpenGL/opengl_fbo.hpp"
#include "OpenGL/opengl_vao.hpp"
#include "physics.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <memory>

namespace flat
{
    class Object : public Rotatable, public Velocitor
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

    class RenableObject : public Object
    {
    private:
        opengl::RectangleVertexArray<opengl::BufferType::Dynamic> rect;

    public:
        RenableObject();
        ~RenableObject();
        // TODO: 提供修改vertices data的API（坐标/颜色/纹理坐标）
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

    class Frame : public RenableObject
    {
    private:
        opengl::FrameBuffer fbo;

    public:
        Frame(int w,int h);
        ~Frame();

        void flush_to_screen();
    };

    // Texture --(RenderPipe)--> Frame
    // Frame.get_texture() --(RenderPipe)--> new Frame
    // Frame.flush_to_screen(): display on screen using default shader
    class Texture : public RenableObject
    {
    private:
        std::unique_ptr<opengl::BasicTexture> texture;

    public:
        Texture(const unsigned char* const data,int x,int y,int w,int h,int channels);
        ~Texture();

        void flush_to_screen();
        // TODO: 应当提供更多的在GPU中处理图像的API
    };

    class CharTexture : public Texture
    {

    };

    class Image : public Object
    {
    private:
        std::unique_ptr<unsigned char[]> bitmap_data;
        int channels;
        int width;
        int height;

    public:
        Image(std::string_view path);
        Image(std::unique_ptr<unsigned char[]> data,int w,int h,int c);
        ~Image();
        std::unique_ptr<Texture> gen_texture(int x,int y,int w,int h);
        // TODO: 应当提供更多的在CPU中处理图像的API
    };

    class Font : public Object
    {
    private:
        FT_Face face;
        unsigned int font_size;

    public:
        Font(std::string_view path);
        ~Font();
        unsigned int get_font_size() const;
        void set_font_size(unsigned int val);
        std::unique_ptr<Texture> gen_char_texture(char32_t c);
    };

    // audio mixer & renderer's camera, all in one
    class Camera : public Object
    {

    };
}