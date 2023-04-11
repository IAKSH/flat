#include "text_renderer.hpp"
#include "../core/window.hpp"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string_view>

ni::flat::TextRenderer::TextRenderer()
{
    initialize();
}

void ni::flat::TextRenderer::initialize()
{
    //shader.loadFromGLSL(vshaderSource,fshaderSource);
	shader.loadFromFile("../../font_vshader.glsl","../../font_fshader.glsl");
    glUniform1i(glGetUniformLocation(shader.getShaderID(), "text"), 0);

	glUseProgram(shader.getShaderID());
	unsigned int camTrans = glGetUniformLocation(shader.getShaderID(), "camTrans");
	auto win = reinterpret_cast<core::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
    glm::mat4 projection = glm::mat4(1.0f) * glm::ortho(0.0f, static_cast<float>(win->getWidth()), 0.0f, static_cast<float>(win->getHeight()), -1.0f, 1.0f);
	glUniformMatrix4fv(camTrans, 1, GL_FALSE, glm::value_ptr(projection));

    indices =
    {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}

void ni::flat::TextRenderer::drawText(std::u32string_view str,const float& x,const float& y,const float& z,const float& r,const float& g,const float& b,const float& a,const float& scale,Font& font)
{
	float _x = x;

	for(int i = 0;i < str.length();i++)
	{
		if(str[i] == '\0')
			break;

		const auto& ch = font.getCharTexture(str[i]);
		GLfloat xpos = _x + ch.getOffsetX() * scale;
        GLfloat ypos = y - (ch.getHeight() - ch.getOffsetY()) * scale;
        GLfloat w = ch.getWidth() * scale;
        GLfloat h = ch.getHeight() * scale;

		vertices = 
		{
			xpos + w,	ypos + h, 	z,	r, g, b, a, 1.0f, 1.0f,  // top right
			xpos + w,	ypos, 		z,	r, g, b, a, 1.0f, 0.0f,  // bottom right
			xpos,		ypos, 		z,	r, g, b, a, 0.0f, 0.0f,  // bottom left
			xpos,		ypos + h, 	z, 	r, g, b, a, 0.0f, 1.0f   // top left
		};

		if(vao.getVAO() == 0)
			vao.create(utils::GLBufferType::Dynamic,vertices,indices);

    	glUseProgram(shader.getShaderID());
		glBindBuffer(GL_ARRAY_BUFFER, vao.getVBO());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
		glBindTexture(GL_TEXTURE_2D,ch.getTextureID());
		glBindVertexArray(vao.getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		_x += (ch.getAdvance() >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
	}
}