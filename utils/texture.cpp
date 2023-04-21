#include "texture.hpp"
#include "logger.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <exception>

ni::utils::Texture::Texture()
	: textureID(0)
{
}

ni::utils::Texture::Texture(std::string_view path)
	: Texture()
{
	loadFromFile(path);
}

ni::utils::Texture::~Texture()
{
	if (textureID)
	{
		utils::coreLogger()->trace("deleting texture with id = {}", textureID);
		glDeleteTextures(1, &textureID);
	}
}

void ni::utils::Texture::loadFromFile(std::string_view path)
{
	utils::coreLogger()->trace("loading texture from {}", path);
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
		utils::coreLogger()->critical("failed to load image file at {}", path.data());
		stbi_image_free(data);
		std::terminate();
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}
