#include "object.hpp"
#include "../../misc/logger.hpp"
#include <exception>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

flat::Image::Image(std::string_view path)
{
    unsigned char* image_data = stbi_load(path.data(),&bitmap_width,&bitmap_height,&bitmap_channels,0);
    if(!image_data)
    {
        misc::main_logger->critical("Failed to load image from {}",path);
        std::terminate();
    }

    bitmap_data = std::unique_ptr<unsigned char[]>(image_data);
}

flat::Image::Image(std::unique_ptr<unsigned char[]> data,int w,int h,int c)
    : bitmap_data(std::move(data)),bitmap_width(w),bitmap_height(h),bitmap_channels(c)
{
}

flat::Image::~Image() = default;