#include "text_renderer.hpp"
#include "../core/window.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string_view>

ni::flat::TextRenderer::TextRenderer()
	: font{nullptr},cam{nullptr},x{0.0f},y{0.0f},scale{1.0f}
{
    initialize();
}

void ni::flat::TextRenderer::initialize()
{
	shader.loadFromGLSL(vshaderSource,fshaderSource);
    glUniform1i(glGetUniformLocation(shader.getShaderID(), "text"), 0);

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

	auto win = reinterpret_cast<core::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
	viewWidth = win->getWidth();
	viewHeight = win->getHeight();
}

void ni::flat::TextRenderer::_drawText()
{
	// TODO: check required data

	if(vao.getVAO() == 0)
			vao.create(utils::GLBufferType::Dynamic,vertices,indices);

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

    	glUseProgram(shader.getShaderID());

		if(cam)
			shader["camTrans"] = UniformArg(cam->getTranslateMatrix());
		else 
		{
			glm::mat4 projection = glm::mat4(1.0f) * glm::ortho(0.0f, viewWidth, 0.0f, viewHeight, -1.0f, 1.0f);
			shader["camTrans"] = UniformArg(projection);
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
	vertices[3] = color.getRed();
	vertices[4] = color.getGreen();
	vertices[5] = color.getBlue();
	vertices[6] = color.getAlpha();
	vertices[12] = color.getRed();
	vertices[13] = color.getGreen();
	vertices[14] = color.getBlue();
	vertices[15] = color.getAlpha();
	vertices[21] = color.getRed();
	vertices[22] = color.getGreen();
	vertices[23] = color.getBlue();
	vertices[24] = color.getAlpha();
	vertices[30] = color.getRed();
	vertices[31] = color.getGreen();
	vertices[32] = color.getBlue();
	vertices[33] = color.getAlpha();
}

void ni::flat::TextRenderer::drawTextHelper(Point&& point)
{
	x = point.getX();
	y = point.getY();
	vertices[2] = point.getZ();
	vertices[11] = point.getZ();
	vertices[20] = point.getZ();
	vertices[29]  = point.getZ();
}

void ni::flat::TextRenderer::drawTextHelper(Scale&& scale)
{
	this->scale = scale;
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