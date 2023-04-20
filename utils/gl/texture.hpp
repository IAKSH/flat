#pragma once

#include <string_view>

#include "disable_copy.hpp"

#include <glad/glad.h>

namespace ni::utils
{
	class TextureCoord
	{
	private:
		float x,y;

	public:
		TextureCoord() : x(0.0f),y(0.0f) {}
		TextureCoord(float x,float y) : x(x),y(y) {}
		~TextureCoord() = default;

		const float& getX() {return x;}
		const float& getY() {return y;}
		void setX(const float& val) {x = val;}
		void setY(const float& val) {y = val;}
	};

	class Texture : public DisableCopy
	{
	private:
		GLuint textureID;

	protected:
		void setTextureID(GLuint id) { textureID = id; }

	public:
		Texture();
		Texture(std::string_view path);
		~Texture();
		const GLuint& getTextureID() const { return textureID; }
		void loadFromFile(std::string_view path);
	};
}