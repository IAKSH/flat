#include <format>
#include <stdexcept>
#include <quick_gl/image.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

quick3d::gl::Image::Image(std::string_view path,bool flip) noexcept(false)
    : img_data(nullptr)
{
    stbi_set_flip_vertically_on_load(flip);
    img_data = stbi_load(path.data(),&img_width,&img_height,&img_channels,0);
    if(!img_data)
        throw std::runtime_error(std::format("failed to load image from {}\n",path));
}

quick3d::gl::Image::~Image() noexcept
{
    stbi_image_free(img_data);
}

unsigned char* quick3d::gl::Image::get_img_data() const noexcept
{
    return img_data;
}

int quick3d::gl::Image::get_img_width() const noexcept
{
    return img_width;
}

int quick3d::gl::Image::get_img_height() const noexcept
{
    return img_height;
}

int quick3d::gl::Image::get_img_channels() const noexcept
{
    return img_channels;
}