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

	vertices = 
	{
		1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
		1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
	};

	if(vao.getVAO() == 0)
		vao.create(utils::GLBufferType::Dynamic,vertices,indices);

	for(int i = 0;i < str.length();i++)
	{
		if(str[i] == '\0')
			break;

		const auto& charTex = font.getCharTexture(str[i]);
		const auto& nextCharTex = font.getCharTexture(str[i + 1]);

		xpos += charTex.getWidth() * scale / 2.0f + 16.0f * scale;

    	glUseProgram(shader.getShaderID());
		glBindTexture(GL_TEXTURE_2D,charTex.getTextureID());
		glm::mat4 trans(1.0f);
		trans *= glm::translate(glm::mat4(1.0f), glm::vec3(xpos + charTex.getOffsetX(),y, z));
		trans *= glm::scale(glm::mat4(1.0f), glm::vec3(charTex.getWidth() * scale,charTex.getHeight() * scale, 1.0f));
		trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		unsigned int transLocation = glGetUniformLocation(shader.getShaderID(), "transform");
		glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));

		glUniform4f(glGetUniformLocation(shader.getShaderID(),"textColor"),0.0f,0.5f,0.8f,0.75f);
		glUniform4f(glGetUniformLocation(shader.getShaderID(),"outlineColor"),1.0f,0.0f,0.0f,0.75f);
		glUniform1f(glGetUniformLocation(shader.getShaderID(),"outlineColor"),0.5f);
		glBindVertexArray(vao.getVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		xpos += charTex.getOffsetX() * scale  + charTex.getWidth() * scale + nextCharTex.getOffsetX() * scale + 16.0f * scale;
	}
}