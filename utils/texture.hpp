#pragma once

#include <string_view>

#include <glad/glad.h>

namespace ni::utils
{
	class Texture
	{
	private:
		GLuint textureID;

	public:
		Texture();
		Texture(std::string_view path);
		~Texture();
		const GLuint& getTextureID() { return textureID; }
		void loadFromFile(std::string_view path);
	};
}