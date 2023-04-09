#pragma once

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
        char c;

    public:
        CharTexture(char c,GLuint texID)
            : c{c}
        {
            setTextureID(texID);
        }
        ~CharTexture() = default;
        const char& getChar() { return c; }
    };

    class Font
    {
    private:
        std::unique_ptr<unsigned char[]> ttfBinary;
        std::deque<std::unique_ptr<CharTexture>> textureCache;

    public:
        Font(std::string_view path);
        Font() = default;
        ~Font() = default;
        const ni::utils::Texture& getCharTexture(const char32_t& c);
        void freeCacheInRange(const char& low,const char& up);
        void loadTTF(std::string_view path);
    };
}