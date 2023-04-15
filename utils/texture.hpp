#pragma once

#include <string_view>

#include <glad/glad.h>

namespace ni::utils
{
	class Texture
	{
	private:
		GLuint textureID;

	protected:
		void setTextureID(GLuint id) { textureID = id; }

	public:
		Texture();
		Texture(Texture&) = delete;
		Texture(std::string_view path);
		~Texture();
		const GLuint& getTextureID() const { return textureID; }
		void loadFromFile(std::string_view path);
	};
}