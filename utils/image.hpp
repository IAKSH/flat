#pragma once

#include <memory>
#include <string>

namespace ni::utils
{
    class Image
    {
    private:
        unsigned int width,height,channels;
        std::unique_ptr<unsigned char[]> data;
        void load(std::string_view path);

    public:
        Image(std::string_view path);
        ~Image() = default;

        const unsigned char* const getData() const {return data.get();}
        const unsigned int& getWidth() const {return width;}
        const unsigned int& getHeight() const {return height;}
        const unsigned int& getChannels() const {return channels;}
    };
}