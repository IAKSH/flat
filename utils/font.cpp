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

const ni::utils::Texture& ni::utils::Font::getCharTexture(const char& c) const
{
    auto ite = std::ranges::find_if(textureCache,[&c](const std::unique_ptr<CharTexture>& tex){return tex->getChar() == c;});
    if(ite != std::end(textureCache))
        return **ite;
    else
    {
        // TODO: load bitmap from ttf and save it to cache (just in time)
    }
}

std::unique_ptr<ni::utils::Texture> ni::utils::Font::getStringTexture(std::string_view str) const
{
    stbtt_fontinfo info;
    if(!stbtt_InitFont_internal(&info,ttfBinary.get(),0))
    {
        ni::utils::coreLogger()->critical("stb init font failed");
        abort();
    }

    size_t bitmapWidth = 64 * str.length();
    constexpr size_t bitmapHeight = 64;

    auto bitmap = std::make_unique<unsigned char[]>(bitmapWidth * bitmapHeight);
    float pixels = 64.0f;
    float scale = stbtt_ScaleForPixelHeight(&info, pixels);
    int ascent = 0;
    int descent = 0;
    int lineGap = 0;
    stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
    ascent = roundf(ascent * scale);
    descent = roundf(descent * scale);
    int x = 0;

    // load all char
    for(const auto& c : str)
    {
        if(c == '\0')
            break;

        int advanceWidth = 0;
        int leftSideBearing = 0;
        stbtt_GetCodepointHMetrics(&info, c, &advanceWidth, &leftSideBearing);

        int c_x1, c_y1, c_x2, c_y2;
        stbtt_GetCodepointBitmapBox(&info, c, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

        int y = ascent + c_y1;

        int byteOffset = x + roundf(leftSideBearing * scale) + (y * bitmapWidth);
        stbtt_MakeCodepointBitmap(&info, bitmap.get() + byteOffset, c_x2 - c_x1, c_y2 - c_y1, bitmapWidth, scale, scale, c);
        
        x += roundf(advanceWidth * scale);

        int kern;
        kern = stbtt_GetCodepointKernAdvance(&info, c, *(&c + 1));
        x += roundf(kern * scale);
    }
    
    // create OpenGL Texture2D
    GLuint textureID;
    glGenTextures(1,&textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmapWidth, bitmapHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.get());
	glGenerateMipmap(GL_TEXTURE_2D);

    return std::make_unique<ni::utils::CharTexture>('s',textureID);
}
