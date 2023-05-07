#pragma once

#include "opengl_texture.hpp"
#include "../core/template.hpp"  
#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <array>
#include <deque>
#include <memory>
#include <string_view>

namespace ni::utils
{
    class CharTexture
    {
        using Texture = opengl::Texture<opengl::ColorChannelType::Red,opengl::ColorChannelType::RGBA>;

    private:
        char32_t c;
        const float scale { 48 };
        int advance;
        std::array<int,2> size;
        std::array<int,2> bearing;
        std::unique_ptr<Texture> texture;

    public:
        CharTexture(unsigned char* data, char32_t c,int s1,int s2,int b1,int b2,int adv)
            : c{c},advance{adv},size{s1,s2},bearing{b1,b2}
        {
            texture = std::make_unique<Texture>(data,0,0,s1,s2);
        }
        ~CharTexture() = default;
        const char32_t& getChar() const { return c; }
        const int& getWidth() const { return size[0]; }
        const int& getHeight() const { return size[1]; }
        const int& getOffsetX() const { return bearing[0]; }
        const int& getOffsetY() const { return bearing[1]; }
        const int& getAdvance() const { return advance; }
        const float& getScale() const { return scale; }
        const GLuint getTextureID() const { return texture->getTextureID(); }
    };

    class Font : public core::DisableCopy
    {
    private:
        FT_Face face;
        unsigned int fontSize;
        std::unique_ptr<unsigned char[]> ttfBinary;
        std::deque<std::unique_ptr<CharTexture>> textureCache;

    public:
        Font(unsigned int size,std::string_view path);
        Font() : fontSize{48} {}
        ~Font();
        const ni::utils::CharTexture& getCharTexture(const char32_t& c);
        void freeCacheInRange(const char& low,const char& up);
        void loadFromFile(std::string_view path);
        void resize(unsigned int size);
    };
}