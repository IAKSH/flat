#include "image.hpp"
#include "../core/loggers.hpp"
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

ni::utils::Image::Image(std::string_view path)
{
    load(path);
}

void ni::utils::Image::load(std::string_view path)
{
    int w,h,c;
    unsigned char* imageData = stbi_load(path.data(),&w,&h,&c,0);
    if (!imageData)
	{
		core::utilsLogger->critical("failed to load image file at {}", path.data());
		std::terminate();
	}

    width = w;
    height = h;
    channels = c;
    data = std::unique_ptr<unsigned char[]>(imageData);
}