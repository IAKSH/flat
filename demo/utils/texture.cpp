#include "texture.hpp"

#include "log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

flat::utils::Texture::Texture()
	: textureID(0)
{
}

flat::utils::Texture::Texture(std::string_view path)
	: Texture()
{
	loadFromFile(path);
}

flat::utils::Texture::~Texture()
{
	if (textureID)
	{
		LOG_TRACE("deleted texture with id = {}", textureID);
		glDeleteTextures(1, &textureID);
	}
}

void flat::utils::Texture::loadFromFile(std::string_view path)
{
	LOG_TRACE("loading texture from {}", path);
	glGenTextures(1, &textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, channels;
	unsigned char* data;

	data = stbi_load(path.data(), &w, &h, &channels, 0);
	if (!data)
	{
		LOG_CRITICAL("failed to load image file at {}", path.data());
		abort();
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	LOG_TRACE("OK");
}
