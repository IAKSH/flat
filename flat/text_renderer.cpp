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

    indices =
    {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}

void ni::flat::TextRenderer::drawText(std::u32string_view str,const float& x,const float& y,const float& z,const float& r,const float& g,const float& b,const float& a,const float& scale,Font& font)
{
    const GLuint shaderID = shader.getShaderID();
    glUseProgram(shaderID);
    // configure projection matrix
    GLint projLoc = glGetUniformLocation(shaderID, "projTrans");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));// for test
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLfloat cursorX = x, cursorY = y;

    for (auto c : str)
    {
        const CharTexture& charTex = font.getCharTexture(c);  // 获取字符对应的纹理信息

        GLfloat xpos = cursorX + charTex.getOffsetX() * scale;
        GLfloat ypos = cursorY - charTex.getHeight() * scale + charTex.getOffsetY() * scale;
        GLfloat w = charTex.getWidth() * scale;
        GLfloat h = charTex.getHeight() * scale;

        // update VBO for each character
        vertices[0] = xpos;        vertices[1] = ypos + h;   vertices[2] = z;   vertices[3] = r;   vertices[4] = g;   vertices[5] = b;   vertices[6] = a;   vertices[7] = 1.0f - charTex.getHeight() / 64.0f;   vertices[8] = charTex.getOffsetX() / 64.0f;
        vertices[9] = xpos;        vertices[10] = ypos;       vertices[11] = z;  vertices[12] = r;   vertices[13] = g;  vertices[14] = b;  vertices[15] = a;  vertices[16] = 1.0f - charTex.getHeight() / 64.0f;   vertices[17] = 1.0f - charTex.getOffsetY() / 64.0f;
        vertices[18] = xpos + w;   vertices[19] = ypos;       vertices[20] = z;  vertices[21] = r;   vertices[22] = g;  vertices[23] = b;  vertices[24] = a;  vertices[25] = 1.0f - charTex.getHeight() / 64.0f + charTex.getWidth() / 64.0f;  vertices[26] = 1.0f - charTex.getOffsetY() / 64.0f;
        vertices[27] = xpos + w;   vertices[28] = ypos + h;   vertices[29] = z;  vertices[30] = r;   vertices[31] = g;  vertices[32] = b;  vertices[33] = a;  vertices[34] = 1.0f - charTex.getHeight() / 64.0f + charTex.getWidth() / 64.0f;  vertices[35] = charTex.getOffsetX() / 64.0f;

        if(vao.getVAO() == 0)
            vao.create(utils::GLBufferType::Dynamic,vertices,indices);

        glBindTexture(GL_TEXTURE_2D, charTex.getTextureID());
        glBindVertexArray(vao.getVAO());
        glBindBuffer(GL_ARRAY_BUFFER, vao.getVBO());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());  // 更新VBO数据
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

        // advance cursor for next glyph (note that advance is number of 1/64 pixels)
        cursorX += (charTex.getWidth() + charTex.getOffsetX()) * scale; // 在每个字符的右侧空出一个像素
    }
}