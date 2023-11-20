#pragma once

#include <cstdint>
#include <concepts>

#include <glad/gles2.h>

// TODO: 实现TBO

namespace quick3d::gl
{
    class Texture
    {
    private:
        GLuint tex_id;
        GLenum tex_format;
        uint32_t tex_width;
        uint32_t tex_height;
        
        bool enable_rtti;
        void generate_texture(GLenum img_format, unsigned char* img_data, uint32_t img_width, uint32_t img_height) noexcept;
        void delete_texture() noexcept;

    public:
        // this will create an empty Texture (with memory allocated)
        Texture(GLenum tex_format,uint32_t tex_width,uint32_t tex_height,bool enable_rtti = true) noexcept;
        Texture(GLenum tex_format,GLenum img_format,unsigned char* img_data,uint32_t img_width,uint32_t img_height,bool enable_rtti = true) noexcept;

        template <typename T>
        requires requires(T t)
        {
            { t.get_img_data() } -> std::convertible_to<const void*>;
            { t.get_img_channels() } -> std::same_as<int>;
            { t.get_img_width() } -> std::same_as<int>;
            { t.get_img_height() } -> std::same_as<int>;
        }
        Texture(GLenum tex_format,const T& t,bool enable_rtti = true) noexcept
        {
            this->enable_rtti = enable_rtti;
            this->tex_format = tex_format;

            GLenum img_format;
            switch(t.get_img_channels())
            {
            case 1: img_format = GL_RED; break;
            case 3: img_format = GL_RGB;    break;
            case 4: img_format = GL_RGBA;   break;
            }

            generate_texture(img_format,t.get_img_data(),t.get_img_width(),t.get_img_height());
        }

        // maybe realized latter
        Texture(Texture& texture) = delete;
        ~Texture() noexcept;

        GLuint get_tex_id() const noexcept;
        GLint get_tex_width() const noexcept;
        GLint get_tex_height() const noexcept;
        GLenum get_tex_format() const noexcept;
    };
}