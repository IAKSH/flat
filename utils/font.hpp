#pragma once

#include <array>
#include <deque>
#include <memory>
#include <string_view>

#include "texture.hpp"
#include "shader.hpp"

#include <glad/glad.h>

namespace ni::utils
{
    class CharTexture : public ni::utils::Texture
    {
    private:
        char32_t c;
        float scale;
        int width,height;
        int offsetX,offsetY;
        int ascent, descent, lineGap;

    public:
        CharTexture(char32_t c,int w,int h,int offsetX,int offsetY,int ascent,int descent,int lineGap,float scale,GLuint texID)
            : c{c},width{w},height{h},offsetX{offsetX},offsetY{offsetY},ascent{ascent},descent{descent},lineGap{lineGap},scale{scale}
        {
            setTextureID(texID);
        }
        ~CharTexture() = default;
        const char32_t& getChar() const { return c; }
        const int& getWidth() const { return width; }
        const int& getHeight() const { return height; }
        const int& getOffsetX() const { return offsetX; }
        const int& getOffsetY() const { return offsetY; }
        const float& getScale() const { return scale; }
        const int& getAscent() const { return ascent; }
        const int& getDescent() const { return descent; }
        const int& getLineGap() const { return lineGap; }
    };

    class Font
    {
    private:
        std::unique_ptr<unsigned char[]> ttfBinary;
        std::deque<std::unique_ptr<CharTexture>> textureCache;

    public:
        Font(std::string_view path);
        Font() = default;
        Font(Font&) = delete;
        ~Font() = default;
        const ni::utils::CharTexture& getCharTexture(const char32_t& c);
        void freeCacheInRange(const char& low,const char& up);
        void loadTTF(std::string_view path);
    };
}