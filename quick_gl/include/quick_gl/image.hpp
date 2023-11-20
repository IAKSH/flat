#pragma once

#include <string_view>

namespace quick3d::gl
{
    class Image
    {
    private:
        unsigned char* img_data;
        int img_width;
        int img_height;
        int img_channels;

    public:
        Image(std::string_view path,bool flip = true) noexcept(false);
        Image(Image&) = delete;
        ~Image() noexcept;

        unsigned char* get_img_data() const noexcept;
        int get_img_width() const noexcept;
        int get_img_height() const noexcept;
        int get_img_channels() const noexcept;
    };
}