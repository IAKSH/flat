#pragma once

#include <cstdint>
#include <concepts>
#include <glad/gles2.h>

namespace quick3d::gl
{
    class CubeMap
    {
    protected:
        GLenum cubemap_format;
        GLuint cubemap_id;
        const uint32_t width;
        const uint32_t height;

        bool positive_x_complete{ false };
        bool positive_y_complete{ false };
        bool positive_z_complete{ false };
        bool negative_x_complete{ false };
        bool negative_y_complete{ false };
        bool negative_z_complete{ false };

        void mark_as_loaded(GLenum location) noexcept;
        void pre_alloc_cubemap(GLenum pre_alloc_format = GL_RGBA) noexcept;

    public:
        CubeMap(GLenum cubemap_format, uint32_t w, uint32_t h) noexcept;
        CubeMap(GLenum cubemap_format, GLenum pre_alloc_format, uint32_t w, uint32_t h) noexcept;
        CubeMap(CubeMap&) = delete;
        ~CubeMap() noexcept;
        GLuint get_cubemap_id() const noexcept;
        uint32_t get_cubemap_width() const noexcept;
        uint32_t get_cubemap_height() const noexcept;
        bool is_cubemap_complete() const noexcept;
    };

    class ColorCubeMap : public CubeMap
    {
    public:
        ColorCubeMap(GLenum cubemap_format,uint32_t w,uint32_t h) noexcept;
        ColorCubeMap(ColorCubeMap&) = delete;
        ~ColorCubeMap() = default;

        // this will regard the size of image as the size of cubemap itself
        // be carefull to use
        void generate_texture(GLenum location,unsigned char* img_data,uint32_t img_channels) noexcept;

        // this will regard the size of image as the size of cubemap itself
        // be carefull to use
        template <typename T>
        requires requires(T t)
        {
            { t.get_img_data() } -> std::convertible_to<const void*>;
            { t.get_img_channels() } -> std::same_as<int>;
        }
        void generate_texture(GLenum location,const T& t) noexcept
        {
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_CUBE_MAP,cubemap_id);

            GLenum img_format;
            switch (t.get_img_channels())
            {
            case 1: img_format = GL_RED;    break;
            case 3: img_format = GL_RGB;  break;
            case 4: img_format = GL_RGBA; break;
            }

            glTexImage2D(location,0,cubemap_format,width,height,0,img_format,GL_UNSIGNED_BYTE,t.get_img_data());
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

            glBindTexture(GL_TEXTURE_CUBE_MAP,0);
            mark_as_loaded(location);
        }
    };

    class DepthCubeMap : public CubeMap
    {
    public:
        DepthCubeMap(uint32_t w, uint32_t h) noexcept;
        DepthCubeMap(DepthCubeMap&) = delete;
        ~DepthCubeMap() = default;
    };
}