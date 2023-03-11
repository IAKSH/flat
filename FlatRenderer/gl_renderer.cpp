#include "gl_renderer.hpp"

#include <iostream>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
    flat::glcore::Rectangle
*/

flat::glcore::Rectangle::Rectangle()
    : vao(0),vbo(0),ebo(0)
{
}

flat::glcore::Rectangle::~Rectangle()
{
    releaseRectangle();
}

void flat::glcore::Rectangle::releaseRectangle()
{
    glDeleteVertexArrays(1,&vao);
}

/*
    flat::glcore::Triangle
*/

flat::glcore::Triangle::Triangle()
    : vao(0),vbo(0),ebo(0)
{
}

flat::glcore::Triangle::~Triangle()
{   
    releaseRectangle();
}

void flat::glcore::Triangle::releaseRectangle()
{
    glDeleteVertexArrays(1,&vao);
}

/*
    flat::glcore::Shader
*/

flat::glcore::Shader::Shader()
    : shaderId(0)
{
}

flat::glcore::Shader::~Shader()
{
    releaseShader();
}

uint32_t flat::glcore::Shader::compileVShader(std::string_view source)
{
    const char *_source = source.data();
	uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1,&_source, nullptr);
	glCompileShader(vertexShaderId);
	return vertexShaderId;
}

uint32_t flat::glcore::Shader::compileFShader(std::string_view source)
{
    const char *_source = source.data();
	uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1,&_source, nullptr);
	glCompileShader(fragmentShaderId);
	return fragmentShaderId;
}

void flat::glcore::Shader::checkVShader(uint32_t vshaderId)
{
	int success;
	char infoLog[512];
	glGetShaderiv(vshaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vshaderId, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "error: failed to compile vertex shader\nshader info log:  " << infoLog << std::endl;
		abort();
	}
}

void flat::glcore::Shader::checkFShader(uint32_t fshaderId)
{
	int success;
	char infoLog[512];
	glGetShaderiv(fshaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fshaderId, sizeof(infoLog), nullptr, infoLog);
		std::cout << "error: failed to compile fragment shader\nshader info log:  " << infoLog << std::endl;
		abort();
	}
}

void flat::glcore::Shader::linkShader(uint32_t vshaderId,uint32_t fshaderId)
{
    shaderId = glCreateProgram();
    glAttachShader(shaderId, vshaderId);
	glAttachShader(shaderId, fshaderId);
	glLinkProgram(shaderId);

	glDeleteShader(vshaderId);
	glDeleteShader(fshaderId);
}

void flat::glcore::Shader::releaseShader()
{
    glDeleteProgram(shaderId);
}

void flat::glcore::Shader::useShader()
{
    glUseProgram(shaderId);
	glUniform1i(glGetUniformLocation(shaderId, "texture0"), 0); // "texture0" -> GL_TEXTURE0
    glUniform1i(glGetUniformLocation(shaderId, "texture1"), 1); // "texture1" -> GL_TEXTURE1
}

void flat::glcore::Shader::compileShader(std::string_view vsource, std::string_view fsource)
{
    uint32_t vshaderId = compileVShader(vsource);
    uint32_t fshaderId = compileFShader(fsource);
    checkVShader(vshaderId);
    checkFShader(vshaderId);
    linkShader(vshaderId,fshaderId);
}

void flat::glcore::Shader::writeUniformMat4(std::string_view uniform, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderId,uniform.data()),1,false,glm::value_ptr(mat));
}

/*
    flat::glcore:Texture
*/

flat::glcore::Texture::Texture()
    : textureId(0)
{
}

flat::glcore::Texture::~Texture()
{
}

void flat::glcore::Texture::releaseTexture()
{
    if(textureId)
        glDeleteTextures(1,&textureId);
}

void flat::glcore::Texture::initTexture()
{
}

void flat::glcore::Texture::loadTextureFromFile(std::string_view path)
{
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
}

void flat::glcore::Texture::checkTexture()
{
    if(!textureId)
    {
        std::cerr << "error: trying to use an empty texture" << std::endl;
        abort();
    }
}

uint32_t const flat::glcore::Texture::getTextureId()
{
    checkTexture();
    return textureId;
}

/*
    flat::glcore::Renderer
*/

flat::glcore::Renderer::Renderer()
{
}

flat::glcore::Renderer::~Renderer()
{
}

void flat::glcore::Renderer::initUniversalShader()
{
    // texture1 did't use, for test only
    static const char* VERTEX_SOURCE = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture0;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
    "   vec4 texColor = texture(texture0,TexCoord) * vec4(ourColor,1.0f);\n"
    "   if(texColor.a < 0.1)\n"
    "       discard;\n"
    "   FragColor = texColor;\n"
    "}\n";

    static const char* FRAGMENT_SOURCE =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "uniform vec2 texOffset;\n"
    "uniform mat4 trans;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = trans * vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "   TexCoord = vec2(aTexCoord.x + texOffset.x, 1.0 - aTexCoord.y + texOffset.y);\n"
    "}\n";

    universalShader.compileShader(std::string(VERTEX_SOURCE),std::string(FRAGMENT_SOURCE));
    universalShader.useShader();
}

void flat::glcore::Renderer::initRenderer()
{
    initUniversalShader();
}

void flat::glcore::Renderer::bindTexture(uint32_t texPortId, flat::Texture &texture)
{
    if(texPortId == 0)
    {
        glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D,texture.getTextureId());
    }
    else if(texPortId == 1)
    {
        glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D,texture.getTextureId());
    }
    else
    {
        std::cerr << "error: only GL_TEXTURE0 & GL_TEXTURE1 are supported" << std::endl;
        abort();
    }
}

void flat::glcore::Renderer::cleanScreen(const flat::RGBAColor &color)
{
    glClearColor(color.r,color.g,color.b,color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void flat::glcore::Renderer::drawPixel(const flat::Pixel &pixel)
{
    // TODO: ...
}

void flat::glcore::Renderer::drawTriangle(const flat::Triangle &triangle)
{
    // TODO: ...
}

void flat::glcore::Renderer::drawRectangle(const flat::Rectangle &rectangle)
{
    // TODO: ...
}

void flat::glcore::Renderer::makeupTriangle(flat::Triangle *triangle)
{
    // TODO: ...
}

void flat::glcore::Renderer::makeupRectangle(flat::Rectangle *rectangle)
{
    // TODO: ...
}