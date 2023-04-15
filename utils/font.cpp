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

namespace ni::utils
{
    static FT_Library ft;
    static bool freetypeLoaded { false };
}

ni::utils::Font::Font(std::string_view path)
{
    loadTTF(path);
}

ni::utils::Font::~Font()
{
    FT_Done_Face(face);
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
    if(!freetypeLoaded)
    {
        if (FT_Init_FreeType(&ft))
        {
            ni::utils::coreLogger()->critical("could not initialize freetype library");
            std::terminate();
        }
        ni::utils::coreLogger()->trace("freetype library loaded");
    }

    ni::utils::coreLogger()->trace("loading ttf from {}",path);
    if (FT_New_Face(ft, path.data(), 0, &face))
    {
        ni::utils::coreLogger()->critical("could not load ttf from {}",path);
        std::terminate();
    }

    // font size = 48
    FT_Set_Pixel_Sizes(face, 0, 48);
}

const ni::utils::CharTexture& ni::utils::Font::getCharTexture(const char32_t& c)
{
    auto ite = std::ranges::find_if(textureCache,[&c](const std::unique_ptr<CharTexture>& tex){return tex->getChar() == c;});
    if(ite != std::end(textureCache))
        return **ite;
    else
    {
        ni::utils::coreLogger()->trace("create texture of 0x{:X} from ttf",static_cast<unsigned int>(c));

        // Load bitmap from TTF and save it to cache
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (FT_Load_Char(face,c,FT_LOAD_RENDER))
        {
            ni::utils::coreLogger()->critical("can't load 0x{:X} from ttf",static_cast<unsigned int>(c));
            std::terminate();
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        auto ptr = std::make_unique<CharTexture>(c,face->glyph->bitmap.width,face->glyph->bitmap.rows,face->glyph->bitmap_left,face->glyph->bitmap_top,face->glyph->advance.x,textureID);
        ni::utils::CharTexture& texture = *ptr;
        textureCache.push_back(std::move(ptr));

        return texture;
    }
}
