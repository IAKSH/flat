#include <deque>
#include <exception>
#include <ios>
#include <iterator>
#include <memory>
#include <new>
#include <ranges>
#include <string>
#include <string_view>
#include <fstream>

#include "font.hpp"
#include "logger.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

ni::utils::Font::Font(std::string_view path)
{
    loadTTF(path);
}

void ni::utils::Font::freeCacheInRange(const char& low,const char& up)
{
    auto filterRange = textureCache | std::views::filter(
        [&](const std::unique_ptr<CharTexture>& ptr) { return ptr->getChar() <= up && ptr->getChar() >= low; });

    std::erase_if(textureCache, [&filterRange,&low,&up](const std::unique_ptr<CharTexture>& ptr) {
        return std::ranges::find(filterRange, ptr) != std::ranges::end(filterRange);
    });
}

void ni::utils::Font::loadTTF(std::string_view path)
{
    try
    {
        ni::utils::coreLogger()->trace("loading ttf from {}",path);
        std::ifstream ifs(path,std::ios::binary);

        if(ifs.is_open())
        {
            ifs.seekg(0, std::ios::end);
            std::streampos size = ifs.tellg();
            ifs.seekg(0, std::ios::beg);
            ttfBinary = std::make_unique<unsigned char[]>(size);
            for(size_t index = 0;!ifs.eof();index++)
                ttfBinary[index] = ifs.get();
            ifs.close();
        }
        else
        {
            ni::utils::coreLogger()->critical("can't open ttf file from {}",path);
            abort();
        }
    }
    catch(const std::bad_alloc& e)
    {
        ni::utils::coreLogger()->critical("cant alloc memory when loading ttf from {}",path);
        abort();
    }
}

const ni::utils::CharTexture& ni::utils::Font::getCharTexture(const char32_t& c)
{
    auto ite = std::ranges::find_if(textureCache,[&c](const std::unique_ptr<CharTexture>& tex){return tex->getChar() == c;});
    if(ite != std::end(textureCache))
        return **ite;
    else
    {
        // Load bitmap from TTF and save it to cache
        stbtt_fontinfo info;
        if(!stbtt_InitFont(&info, ttfBinary.get(), 0))
        {
            ni::utils::coreLogger()->critical("stb init font failed");
            abort();
        }

        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
        float scale = stbtt_ScaleForPixelHeight(&info, 64.0f);

        int width, height, offset_x, offset_y;
        unsigned char* bitmap = stbtt_GetCodepointBitmap(&info, scale, scale, c, &width, &height, &offset_x, &offset_y);

        GLuint textureID;

        // create texture
        glGenTextures(1, &textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
        glGenerateMipmap(GL_TEXTURE_2D);

        auto ptr = std::make_unique<CharTexture>(c,width,height,offset_x,offset_y,textureID);
        ni::utils::CharTexture& texture = *ptr;
        textureCache.push_back(std::move(ptr));

        stbtt_FreeBitmap(bitmap, nullptr);

        return texture;
    }
}
