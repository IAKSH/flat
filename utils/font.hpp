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
        int width,height;     // 字形大小
        int offsetX,offsetY;  // 从基准线到字形左部/顶部的偏移值
        //unsigned int advance;       // 原点距下一个字形原点的距离

    public:
        CharTexture(char32_t c,int w,int h,int offsetX,int offsetY,GLuint texID)
            : c{c},width{w},height{h},offsetX{offsetX},offsetY{offsetY}
        {
            setTextureID(texID);
        }
        ~CharTexture() = default;
        const char32_t& getChar() const { return c; }
        const int& getWidth() const { return width; }
        const int& getHeight() const { return height; }
        const int& getOffsetX() const { return offsetX; }
        const int& getOffsetY() const { return offsetY; }
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