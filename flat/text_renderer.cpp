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
	float xpos = x;

	for(int i = 0;i < str.length();i++)
	{
		if(str[i] == '\0')
			break;

		const auto& charTex = font.getCharTexture(str[i]);
		//const auto& nextCharTex = font.getCharTexture(str[i + 1]);

		float scaledWidth = charTex.getWidth() * scale;
		float scaledHeight = charTex.getHeight() * scale;
		float scaledOffsetX = charTex.getOffsetX() * scale;
		float scaledOffsetY = charTex.getOffsetY() * scale;

		vertices = 
		{
			xpos - scaledOffsetX + scaledWidth,  y - scaledOffsetY / 2.0f + scaledHeight / 2.0f, z, r, g, b, a, 1.0f, 1.0f,  // top right
			xpos - scaledOffsetX + scaledWidth,  y - scaledOffsetY / 2.0f - scaledHeight / 2.0f, z, r, g, b, a, 1.0f, 0.0f,  // bottom right
			xpos - scaledOffsetX , y - scaledOffsetY / 2.0f - scaledHeight / 2.0f, z, r, g, b, a, 0.0f, 0.0f,  // bottom left
			xpos - scaledOffsetX, y - scaledOffsetY / 2.0f + scaledHeight / 2.0f,  z, r, g, b, a, 0.0f, 1.0f   // top left
		};

		if(vao.getVAO() == 0)
			vao.create(utils::GLBufferType::Dynamic,vertices,indices);

		xpos += charTex.getWidth() * scale / 2.0f + 16.0f * scale;

    	glUseProgram(shader.getShaderID());
		glBindBuffer(GL_ARRAY_BUFFER, vao.getVBO());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
		glBindTexture(GL_TEXTURE_2D,charTex.getTextureID());
		glBindVertexArray(vao.getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//xpos += scaledOffsetX + scaledWidth;
		xpos += (scaledWidth - scaledOffsetX) / 2.0f;
	}
}