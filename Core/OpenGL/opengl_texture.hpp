#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/abstract_base.hpp"
#include "opengl_scope.hpp"
#include <glad/glad.h>
#include <exception>
#include <string>

namespace flat::opengl
{
    enum class ColorChannel
    {
        Red_Only,Blue_Only,Green_Only,Alpha_Obly,RGB,RGBA
    };

    class BasicTexture
    {
    protected:
        GLuint texture_id;
        const unsigned int origin_x,origin_y,width,height;
        
        BasicTexture(const unsigned char* const data,unsigned int x,unsigned int y,unsigned int w,unsigned int h)
            : origin_x(x),origin_y(y),width(w),height(h)
        {
        }

    public:
        ~BasicTexture()
        {
            glDeleteTextures(1,&texture_id);
        }

        const GLuint& get_texture_id() const {return texture_id;}
        unsigned int get_origin_x() const {return origin_x;}
        unsigned int get_origin_y() const {return origin_y;}
        unsigned int get_width() const {return width;}
        unsigned int get_height() const {return height;}
    };

    template <ColorChannel image_channel,ColorChannel texture_channel>
    class Texture : public BasicTexture, misc::DisableCopy
    {
    public:
        Texture(const unsigned char* const data,unsigned int x,unsigned int y,unsigned int w,unsigned int h)
            : BasicTexture(data,x,y,w,h)
        {
            Scope scope;

            glGenTextures(1,&texture_id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int image_channel_bits,image_channel_enum;
            if constexpr(image_channel == ColorChannel::Red_Only)
            {
                image_channel_bits = 1;
                image_channel_enum = GL_RED;
            }
            else if constexpr(image_channel == ColorChannel::Green_Only)
            {
                image_channel_bits = 1;
                image_channel_enum = GL_GREEN;
            }
            else if constexpr(image_channel == ColorChannel::Blue_Only)
            {
                image_channel_bits = 1;
                image_channel_enum = GL_GREEN;
            }
            else if constexpr(image_channel == ColorChannel::Alpha_Obly)
            {
                image_channel_bits = 1;
                image_channel_enum = GL_ALPHA;
            }
            else if constexpr(image_channel == ColorChannel::RGB)
            {
                image_channel_bits = 3;
                image_channel_enum = GL_RGB;
            }
            else if constexpr(image_channel == ColorChannel::RGBA)
            {
                image_channel_bits = 4;
                image_channel_enum = GL_RGBA;
            }

            int texture_channel_enum;
            if constexpr(texture_channel == ColorChannel::Red_Only)
                texture_channel_enum = GL_RED;
            else if constexpr(texture_channel == ColorChannel::Green_Only)
                texture_channel_enum = GL_GREEN;
            else if constexpr(texture_channel == ColorChannel::Blue_Only)
                texture_channel_enum = GL_BLUE;
            else if constexpr(texture_channel == ColorChannel::Alpha_Obly)
                texture_channel_enum = GL_ALPHA;
            else if constexpr(texture_channel == ColorChannel::RGB)
                texture_channel_enum = GL_RGB;
            else if constexpr(texture_channel == ColorChannel::RGBA)
                texture_channel_enum = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D,texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, texture_channel_enum, width, height, 0, image_channel_enum, GL_UNSIGNED_BYTE, data + (origin_y * width + origin_x) * image_channel_bits);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        ~Texture() = default;
    };
}