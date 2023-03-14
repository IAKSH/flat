#include "glcore_renderer.hpp"
#include "glm/fwd.hpp"

#include <iostream>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
    glcore::Texture
*/

glcore::Texture::~Texture()
{
    // TODO: release the Texture
}

/*
    glcore::Font
*/

glcore::Font::~Font()
{
    // TODO: release the font
}

dggen::Font& glcore::Font::operator()(const dggen::Font& font)
{
    // TODO: set Text and then return itself
}

glcore::Renderer::Renderer() : vao(0), vbo(0), ebo(0), shaderProgram(0)
{
    uint32_t vshader = compileVertexShader();
    uint32_t fshader = compileFragmentShader();
    checkFragmentShader(vshader);
    checkVertexShader(fshader);
    makeShaderProgram(vshader, fshader);

    makeDrawMeta();
}

glcore::Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
}

void glcore::Renderer::makeDrawMeta()
{
    // create VAO part1
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create VBO
    float vertices[]{ 1.0f, 1.0f, 0.0, 1.0, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create EBO
    const uint32_t indices[] = { 0, 1, 3, 1, 3, 2 };

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // create VAO part2
    // only vertex position attrib, because we transform/set color/bind texture coords in shader using glsl uniform
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void glcore::Renderer::makeShaderProgram(uint32_t vshader, uint32_t fshader)
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshader);
    glAttachShader(shaderProgram, fshader);
    glLinkProgram(shaderProgram);
    glDeleteProgram(vshader);
    glDeleteProgram(fshader);
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture0"), 0);
}

void glcore::Renderer::checkVertexShader(uint32_t vshader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vshader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "error: failed to compile vertex shader\nshader info log:  " << infoLog << std::endl;
        abort();
    }
}

void glcore::Renderer::checkFragmentShader(uint32_t fshader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fshader, sizeof(infoLog), nullptr, infoLog);
        std::cout << "error: failed to compile fragment shader\nshader info log:  " << infoLog << std::endl;
        abort();
    }
}

uint32_t glcore::Renderer::compileVertexShader()
{
    static const char* VERTEX_SOURCE = "#version 330 core\n"
                                       "layout (location = 0) in vec3 aPos;\n"
                                       "layout (location = 1) in vec3 aColor;\n"
                                       "layout (location = 2) in vec2 aTexCoord;\n"
                                       "out vec3 ourColor;\n"
                                       "out vec2 TexCoord;\n"
                                       "uniform vec2 texOffset;\n"
                                       "uniform mat4 transform;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   gl_Position = transform * vec4(aPos, 1.0);\n"
                                       "   ourColor = aColor;\n"
                                       "   TexCoord = vec2(aTexCoord.x + texOffset.x, 1.0 - aTexCoord.y + texOffset.y);\n"
                                       "}\n";

    uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &VERTEX_SOURCE, nullptr);
    glCompileShader(vertexShaderId);
    return vertexShaderId;
}

uint32_t glcore::Renderer::compileFragmentShader()
{
    static const char* FRAGMENT_SOURCE = "#version 330 core\n"
                                         "out vec4 FragColor;\n"
                                         "in vec3 ourColor;\n"
                                         "in vec2 TexCoord;\n"
                                         "uniform sampler2D texture0;\n"
                                         "uniform sampler2D texture1;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   vec4 texColor = mix(texture(texture0,TexCoord),texture(texture1,TexCoord),0.5) * vec4(ourColor,1.0f);\n"
                                         "   if(texColor.a < 0.1)\n"
                                         "       discard;\n"
                                         "   FragColor = texColor;\n"
                                         "}\n";

    uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &FRAGMENT_SOURCE, nullptr);
    glCompileShader(fragmentShaderId);
    return fragmentShaderId;
}

void glcore::Renderer::writeTransformUniform(const glm::mat4& trans) { glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans)); }

void glcore::Renderer::writeColorUniform(const glm::vec4 color) { glUniform4fv(glGetUniformLocation(shaderProgram, "color"), 1, glm::value_ptr(color)); }

void glcore::Renderer::writeTextCoordsUniform(const glm::vec2 coord1, const glm::vec2 coord2, const glm::vec2 coord3, const glm::vec2 coord4)
{
    glUniform2fv(glGetUniformLocation(shaderProgram, "coord1"), 1, glm::value_ptr(coord1));
    glUniform2fv(glGetUniformLocation(shaderProgram, "coord2"), 1, glm::value_ptr(coord2));
    glUniform2fv(glGetUniformLocation(shaderProgram, "coord3"), 1, glm::value_ptr(coord3));
    glUniform2fv(glGetUniformLocation(shaderProgram, "coord4"), 1, glm::value_ptr(coord4));
}

void glcore::Renderer::imp_setColor(dggen::Color&& color) { writeColorUniform(glm::vec4(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha())); }

void glcore::Renderer::imp_bindTexture(dggen::Texture&& texture)
{
    if(typeid(texture) != typeid(Texture))
    {
        std::cerr << "error: unknow textrue type" << std::endl;
        abort();
    }

    auto& tex = (Texture&)texture;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.getTextureId());
}

void glcore::Renderer::imp_drawRectangle(dggen::Rectangle&& rectangle)
{
    glm::mat4 transfom(1.0f);
    transfom *= glm::translate(transfom, glm::vec3(rectangle.getX(), rectangle.getY(), rectangle.getZ()));
    transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateX(), glm::vec3(1.0f, 0.0f, 0.0f));
    transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateY(), glm::vec3(0.0f, 1.0f, 0.0f));
    transfom *= glm::rotate(glm::mat4(1.0f), rectangle.getRotateZ(), glm::vec3(0.0f, 0.0f, 1.0f));
    writeTransformUniform(transfom);
}

void glcore::Renderer::imp_drawText(dggen::Texture&& text)
{
    // TODO
}

void glcore::Renderer::imp_flush()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

const dggen::Texture& glcore::Renderer::imp_genTexture(std::string_view path)
{
    uint32_t textureId;
    glGenTextures(1, &textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, channels;
	unsigned char *data;

	data = stbi_load(path.data(), &w, &h, &channels, 0);
	if (!data)
	{
		std::cerr << "[ERROR] Can't load " << path.data() << std::endl;
		abort();
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
    return std::move(Texture(textureId));
}

const dggen::Font& glcore::Renderer::imp_genFont(std::string_view path)
{
    // TODO
}