#pragma once

#include "../core/template.hpp"
#include <exception>
#include <glad/glad.h>
#include <string>

namespace ni::utils::opengl
{
    enum class ColorChannelType
    {
        Red,Blue,Green,Alpha,RGB,RGBA
    };

    template <ColorChannelType imageChannelType,ColorChannelType textureChannelType>
    class Texture : public core::DisableCopy
    {
    private:
        GLuint textureID;
        const unsigned int oriX,oriY,width,height;
        void create(const unsigned char* const data)
        {
            glGenTextures(1, &textureID);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int imagechannelBits,imageChannelEnum;
            if constexpr (imageChannelType == ColorChannelType::Red)
            {
                imagechannelBits = 1;
                imageChannelEnum = GL_RED;
            }
            else if constexpr (imageChannelType == ColorChannelType::Green)
            {
                imagechannelBits = 1;
                imageChannelEnum = GL_GREEN;
            }
            else if constexpr (imageChannelType == ColorChannelType::Blue)
            {
                imagechannelBits = 1;
                imageChannelEnum = GL_BLUE;
            }
            else if constexpr (imageChannelType == ColorChannelType::Alpha)
            {
                imagechannelBits = 1;
                imageChannelEnum = GL_ALPHA;
            }
            else if constexpr (imageChannelType == ColorChannelType::RGB)
            {
                imagechannelBits = 3;
                imageChannelEnum = GL_RGB;
            }
            else if constexpr (imageChannelType == ColorChannelType::RGBA)
            {
                imagechannelBits = 4;
                imageChannelEnum = GL_RGBA;
            }

            int textureChannelEnum;
            if constexpr (textureChannelType == ColorChannelType::Red)
                textureChannelEnum = GL_RED;
            else if constexpr (textureChannelType == ColorChannelType::Green)
                textureChannelEnum = GL_GREEN;
            else if constexpr (textureChannelType == ColorChannelType::Blue)
                textureChannelEnum = GL_BLUE;
            else if constexpr (textureChannelType == ColorChannelType::Alpha)
                textureChannelEnum = GL_ALPHA;
            else if constexpr (textureChannelType == ColorChannelType::RGB)
                textureChannelEnum = GL_RGB;
            else if constexpr (textureChannelType == ColorChannelType::RGBA)
                textureChannelEnum = GL_RGBA;


	        glBindTexture(GL_TEXTURE_2D, textureID);
	        glTexImage2D(GL_TEXTURE_2D, 0, textureChannelEnum, width, height, 0, imageChannelEnum, GL_UNSIGNED_BYTE, data + (oriY * width + oriX) * imagechannelBits);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    public:
        Texture(const unsigned char* const data,const unsigned int& x,const unsigned int& y,const unsigned int& w,const unsigned int& h)
            : oriX(x),oriY(y),width(w),height(h)
        {
            create(data);
        }
        ~Texture()
        {
            if(textureID)
                glDeleteTextures(1, &textureID);
        }

        const GLuint& getTextureID() {return textureID;}
        const unsigned int& getOriginX() {return oriX;}
        const unsigned int& getOriginY() {return oriY;}
        const unsigned int& getWidth() {return width;}
        const unsigned int& getHeight() {return height;}
    };
}