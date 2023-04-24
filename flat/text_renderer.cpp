#include "text_renderer.hpp"
#include "../core/application.hpp"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <exception>
#include <string_view>

ni::flat::TextRenderer::TextRenderer()
	: font{nullptr},cam{nullptr},x{0.0f},y{0.0f},scale{1.0f},shader(vshaderSource,fshaderSource)
{
    initialize();
}

void ni::flat::TextRenderer::initialize()
{
	shader.setUniform("text",0);

    indices =
    {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	vertices[7] = 1.0f;
	vertices[8] = 1.0f;
	vertices[16] = 1.0f;
	vertices[17] = 0.0f;
	vertices[25] = 0.0f;
	vertices[26] = 0.0f;
	vertices[34] = 0.0f;
	vertices[35] = 1.0f;

	auto win = reinterpret_cast<core::WindowBackends*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	viewWidth = win->getWidth();
	viewHeight = win->getHeight();
}

void ni::flat::TextRenderer::_drawText()
{
	if(!font)
	{
		ni::core::otherLogger->critical("no font given to TextRenderer");
		std::terminate();
	}

	float _x = x;

	for(int i = 0;i < str.length();i++)
	{
		const auto& ch = font->getCharTexture(str[i]);
		GLfloat xpos = _x + ch.getOffsetX() * scale;
        GLfloat ypos = y - (ch.getHeight() - ch.getOffsetY()) * scale;
        GLfloat w = ch.getWidth() * scale;
        GLfloat h = ch.getHeight() * scale;

		vertices[0] = xpos + w;
		vertices[1] = ypos + h;
		vertices[9] = xpos + w;
		vertices[10] = ypos;
		vertices[18] = xpos;
		vertices[19] = ypos;
		vertices[27] = xpos;
		vertices[28] = ypos + h;

    	shader.use();

		if(cam)
			shader.setUniform("camTrans",cam->getTranslateMatrix());
		else 
		{
			glm::mat4 projection = glm::mat4(1.0f) * glm::ortho(0.0f, viewWidth, 0.0f, viewHeight, -1.0f, 1.0f);
			shader.setUniform("camTrans",projection);
		}

		glBindBuffer(GL_ARRAY_BUFFER, vao.getVBO());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
		glBindTexture(GL_TEXTURE_2D,ch.getTextureID());
		glBindVertexArray(vao.getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		_x += (ch.getAdvance() >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
	}

	if(cam) cam = nullptr;
}

void ni::flat::TextRenderer::drawTextHelper(Color&& color)
{
	for(size_t i = 0;i < 4;i++)
	{
		vertices[3 + i * 9] = color.getRed();
		vertices[4 + i * 9] = color.getGreen();
		vertices[5 + i * 9] = color.getBlue();
		vertices[6 + i * 9] = color.getAlpha();
	}
}

void ni::flat::TextRenderer::drawTextHelper(Point&& point)
{
	x = point.getPositionX();
	y = point.getPositionY();
	for(size_t i = 0;i < 4;i++)
		vertices[2 + i * 9] = point.getPositionZ();
}

void ni::flat::TextRenderer::drawTextHelper(Scale&& scale)
{
	this->scale = scale.get();
}

void ni::flat::TextRenderer::drawTextHelper(Font* font)
{
	this->font = font;
}

void ni::flat::TextRenderer::drawTextHelper(Camera* cam)
{
	this->cam = cam;
}

void ni::flat::TextRenderer::drawTextHelper(std::u32string_view str)
{
	this->str = str;
}
