#include "text_renderer.hpp"
#include "../core/window.hpp"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ni::flat::TextRenderer::TextRenderer()
{
    initialize();
}

void ni::flat::TextRenderer::initialize()
{
    shader.loadFromGLSL(vshaderSource,fshaderSource);
    glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture0"), 0);

}

void ni::flat::TextRenderer::drawText(std::u32string_view str,const float& x,const float& y,const float& r,const float& g,const float& b,const float& a,const float& z,const float& scale,Font& font)
{
    glUseProgram(shader.getShaderID());
    float xpos = x;

    for (const auto& c : str)
    {
        if(c == '\0') break;
        
        const auto& charTex = font.getCharTexture(c);
        float xoffset = charTex.getOffsetX() * scale;
        float yoffset = (charTex.getHeight() - charTex.getOffsetY()) * scale;
        float w = charTex.getWidth() * scale;
        float h = charTex.getHeight() * scale;
        vertices =
        {
            xpos + xoffset,     y - yoffset + h, z, r,g,b,a,   0.0, 0.0,
            xpos + xoffset,     y - yoffset, z, r,g,b,a,      0.0, 1.0,
            xpos + xoffset + w, y - yoffset, z, r,g,b,a,      1.0, 1.0,
            xpos + xoffset + w, y - yoffset + h, z, r,g,b,a,  1.0, 0.0
        };
        indices = 
        {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

        if(vao.getVAO() == 0)
            vao.create(utils::GLBufferType::Dynamic, vertices,indices);

        auto win = reinterpret_cast<core::Window*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
        glm::mat4 trans = glm::mat4(1.0f) * glm::ortho(0.0f, static_cast<float>(win->getWidth()), 0.0f, static_cast<float>(win->getHeight()), -1.0f, 1.0f);

		unsigned int transLocation = glGetUniformLocation(shader.getShaderID(), "projTrans");
		glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));

        glBindTexture(GL_TEXTURE_2D, charTex.getTextureID());
        glBindVertexArray(vao.getVAO());
        glBindBuffer(GL_ARRAY_BUFFER, vao.getVBO());
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_DYNAMIC_DRAW);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        xpos += (charTex.getWidth() + font.getCharTexture(*(&c + 1)).getOffsetX()) * scale;
    }
}