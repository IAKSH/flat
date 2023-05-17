#include "object.hpp"
#include "../../Misc/logger.hpp"
#include <exception>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

flat::Image::Image(std::string_view path)
{
    unsigned char* image_data = stbi_load(path.data(),&width,&height,&channels,0);
    if(!image_data)
    {
        misc::main_logger->critical("Failed to load image from {}",path);
        std::terminate();
    }

    bitmap_data = std::unique_ptr<unsigned char[]>(image_data);
}

flat::Image::Image(std::unique_ptr<unsigned char[]> data,int w,int h,int c)
    : bitmap_data(std::move(data)),width(w),height(h),channels(c)
{
}

flat::Image::~Image() = default;

std::unique_ptr<flat::Texture> flat::Image::gen_texture(int x,int y,int w,int h)
{
    return std::make_unique<Texture>(bitmap_data.get(),x,y,w,h,channels);
}