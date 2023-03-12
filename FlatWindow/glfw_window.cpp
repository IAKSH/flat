#include "glfw_window.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
    flat::gl::FWWindow :  public Window, public KeyboardInputSource, public MouseInputSource
*/

flat::gl::FWWindow::FWWindow()
{
}

flat::gl::FWWindow::~FWWindow() {}

void flat::gl::FWWindow::initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "error: can't get load glad" << std::endl;
        abort();
    }
}

void flat::gl::FWWindow::initGLFW()
{
    glfwInit();
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glWindowHint(gl_OPENGL_FORWARD_COMPAT, GL_TRUE);

    initErrorCallback();

    window = glfwCreateWindow(800, 600, "FALT", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "error: can't create gl window" << std::endl;
        abort();
    }

    //glSwapInterval(3);
}

void flat::gl::FWWindow::initViewport()
{
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height){ glViewport(0, 0, width, height); });
}

void flat::gl::FWWindow::initErrorCallback()
{
    glfwSetErrorCallback([](int error, const char* description){
        std::cout << "gl Error | errno: " << errno << " description: " << description << std::endl;});
}

void flat::gl::FWWindow::initUniversalShader()
{
    static const char* FRAGMENT_SOURCE = 
    "#version 330 core\n"
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

    static const char* VERTEX_SOURCE =
    "#version 330 core\n"
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

    universalShader.compileShader(std::string(VERTEX_SOURCE),std::string(FRAGMENT_SOURCE));
    universalShader.useShader();
}

void flat::gl::FWWindow::initWindow()
{
    initGLFW();
    bindContext();
    initGLAD();
    initViewport();
    initUniversalShader();
}

void flat::gl::FWWindow::destroyWindow()
{
    glfwDestroyWindow(window);
}

void flat::gl::FWWindow::bindContext()
{
    glfwMakeContextCurrent(window);
}

void flat::gl::FWWindow::setWindowHeight(int h)
{
    int buffer;
    glfwGetWindowSize(window,&buffer,nullptr);
    glfwSetWindowSize(window,buffer,h);
}

void flat::gl::FWWindow::setWindowWidth(int w)
{
    int buffer;
    glfwGetWindowSize(window,nullptr,&buffer);
    glfwSetWindowSize(window,w,buffer);
}

void flat::gl::FWWindow::setWindowTitle(std::string_view t)
{
    glfwSetWindowTitle(window,t.data());
}

void flat::gl::FWWindow::setWindowPosition(int x,int y)
{
    glfwSetWindowPos(window,x,y);
}

int const flat::gl::FWWindow::getWindowPositionX()
{
    int buffer;
    glfwGetWindowPos(window,&buffer,nullptr);
    return buffer;
}

int const flat::gl::FWWindow::getWindowPositionY()
{
    int buffer;
    glfwGetWindowPos(window,nullptr,&buffer);
    return buffer;
}

int const flat::gl::FWWindow::getWindowWidth()
{
    int buffer;
    glfwGetWindowSize(window,&buffer,nullptr);
    return buffer;
}

int const flat::gl::FWWindow::getWindowHeight()
{
    int buffer;
    glfwGetWindowSize(window,nullptr,&buffer);
    return buffer;
}

void const flat::gl::FWWindow::updateWindow()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool const flat::gl::FWWindow::checkKeyboardDown(int code)
{
    return glfwGetKey(window,code) == GLFW_PRESS;
}

bool const flat::gl::FWWindow::checkKeyboardUp(int code)
{
    return glfwGetKey(window,code) == GLFW_RELEASE;
}

bool const flat::gl::FWWindow::checkMouseLeft()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
}

bool const flat::gl::FWWindow::checkMouseRight()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
}

bool const flat::gl::FWWindow::checkMouseMiddle()
{
    return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_MIDDLE);
}

double const flat::gl::FWWindow::getMousePosX()
{
    double buffer;
    glfwGetCursorPos(window,&buffer,nullptr);
    return buffer;
}

double const flat::gl::FWWindow::getMousePosY()
{
    double buffer;
    glfwGetCursorPos(window,nullptr,&buffer);
    return buffer;
}

/*
    flat::gl::FWWindow : public Renderer
*/

void flat::gl::FWWindow::bindTexture(uint32_t texPortId, flat::Texture &texture)
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

void flat::gl::FWWindow::cleanScreen(const RGBAColor& color)
{
    glClearColor(color.r,color.g,color.b,color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void flat::gl::FWWindow::drawPixel(const Pixel& pixel)
{
    // TODO
}

void flat::gl::FWWindow::drawRectangle(const flat::Rectangle &rectangle)
{
    // TODO
    const auto ptr = dynamic_cast<flat::gl::Rectangle*>(const_cast<flat::Rectangle*>(&rectangle));
    if(!ptr->vao)
    {
        std::cerr << "error: trying to draw an empty rectangle" << std::endl;
        abort();
    }

    // transform
    glm::mat4 transfom(1.0f);
    //transfom *= glm::scale(transfom,glm::vec3(ptr->))
    transfom *= glm::translate(glm::mat4(1.0f),glm::vec3(ptr->x,ptr->y,ptr->z));
    transfom *= glm::rotate(glm::mat4(1.0f),ptr->rotateX,glm::vec3(1.0f,0.0f,0.0f));
    transfom *= glm::rotate(glm::mat4(1.0f),ptr->rotateY,glm::vec3(0.0f,1.0f,0.0f));
    transfom *= glm::rotate(glm::mat4(1.0f),ptr->rotateZ,glm::vec3(0.0f,0.0f,1.0f));
    

    universalShader.writeUniformMat4("transform",transfom);

    glBindVertexArray(ptr->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void flat::gl::FWWindow::drawTriangle(const flat::Triangle &triangle)
{
    // TODO
}

void flat::gl::FWWindow::makeupTriangle(flat::Triangle *triangle)
{
    // TODO
    //auto ptr = dynamic_cast<flat::gl::Triangle*>(triangle);
}

void flat::gl::FWWindow::makeupRectangle(flat::Rectangle *rectangle)
{
    // TODO
    auto ptr = dynamic_cast<flat::gl::Rectangle*>(rectangle);

    // create VAO part1
    glGenVertexArrays(1, &ptr->vao);
	glBindVertexArray(ptr->vao);

    // create VBO
    float z = ptr->z;
	float hh = ptr->h / 2.0f;
	float hw = ptr->w / 2.0f;
    float r1 = ptr->colors[0].r;
    float g1 = ptr->colors[0].g;
    float b1 = ptr->colors[0].b;
    float a1 = ptr->colors[0].a;
    float r2 = ptr->colors[1].r;
    float g2 = ptr->colors[1].g;
    float b2 = ptr->colors[1].b;
    float a2 = ptr->colors[1].a;
    float r3 = ptr->colors[2].r;
    float g3 = ptr->colors[2].g;
    float b3 = ptr->colors[2].b;
    float a3 = ptr->colors[2].a;
    float r4 = ptr->colors[3].r;
    float g4 = ptr->colors[3].g;
    float b4 = ptr->colors[3].b;
    float a4 = ptr->colors[3].a;
    float t1x = ptr->texCoord1[0];
    float t1y = ptr->texCoord1[1];
    float t2x = ptr->texCoord2[0];
    float t2y = ptr->texCoord2[1];
    float t3x = ptr->texCoord3[0];
    float t3y = ptr->texCoord3[1];
    float t4x = ptr->texCoord4[0];
    float t4y = ptr->texCoord4[1];


	float vertices[]{
		hw, hh, z, r1, g1, b1, t1x ,t1y,
		hw, -1.0f * hh, z, r2 ,g2, b2, t2x, t2y,
		-1.0f * hw, -1.0f * hh, z, r3, g3, b3, t3x, t3y,
		-1.0f * hw, hh, z, r4, g4, b4, t4x, t4y};

	glGenBuffers(1, &ptr->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ptr->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create EBO
    const uint32_t indices[] =
		{
			0, 1, 3,
			1, 3, 2};

	glGenBuffers(1, &ptr->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ptr->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // create VAO part2
    // vertex position attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// vertex color attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

/*
    flat::gl:Texture
*/

flat::gl::Texture::Texture()
    : textureId(0)
{
}

flat::gl::Texture::~Texture()
{
}

void flat::gl::Texture::releaseTexture()
{
    if(textureId)
        glDeleteTextures(1,&textureId);
}

void flat::gl::Texture::initTexture()
{
}

void flat::gl::Texture::loadTextureFromFile(std::string_view path)
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

void flat::gl::Texture::checkTexture()
{
    if(!textureId)
    {
        std::cerr << "error: trying to use an empty texture" << std::endl;
        abort();
    }
}

uint32_t const flat::gl::Texture::getTextureId()
{
    checkTexture();
    return textureId;
}

/*
    flat::gl::Shader
*/

flat::gl::Shader::Shader()
    : shaderId(0)
{
}

flat::gl::Shader::~Shader()
{
    releaseShader();
}

uint32_t flat::gl::Shader::compileVShader(std::string_view source)
{
    const char *_source = source.data();
	uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1,&_source, nullptr);
	glCompileShader(vertexShaderId);
	return vertexShaderId;
}

uint32_t flat::gl::Shader::compileFShader(std::string_view source)
{
    const char *_source = source.data();
	uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1,&_source, nullptr);
	glCompileShader(fragmentShaderId);
	return fragmentShaderId;
}

void flat::gl::Shader::checkVShader(uint32_t vshaderId)
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

void flat::gl::Shader::checkFShader(uint32_t fshaderId)
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

void flat::gl::Shader::linkShader(uint32_t vshaderId,uint32_t fshaderId)
{
    shaderId = glCreateProgram();
    glAttachShader(shaderId, vshaderId);
	glAttachShader(shaderId, fshaderId);
	glLinkProgram(shaderId);

	glDeleteShader(vshaderId);
	glDeleteShader(fshaderId);
}

void flat::gl::Shader::releaseShader()
{
    glDeleteProgram(shaderId);
}

void flat::gl::Shader::useShader()
{
    glUseProgram(shaderId);
	glUniform1i(glGetUniformLocation(shaderId, "texture0"), 0); // "texture0" -> GL_TEXTURE0
    glUniform1i(glGetUniformLocation(shaderId, "texture1"), 1); // "texture1" -> GL_TEXTURE1
}

void flat::gl::Shader::compileShader(std::string_view vsource, std::string_view fsource)
{
    uint32_t vshaderId = compileVShader(vsource);
    uint32_t fshaderId = compileFShader(fsource);
    checkVShader(vshaderId);
    checkFShader(vshaderId);
    linkShader(vshaderId,fshaderId);
}

void flat::gl::Shader::writeUniformMat4(std::string_view uniform, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderId,uniform.data()),1,GL_FALSE,glm::value_ptr(mat));
}

/*
    flat::gl::Triangle
*/

flat::gl::Triangle::Triangle()
    : vao(0),vbo(0),ebo(0)
{
}

flat::gl::Triangle::~Triangle()
{   
    releaseRectangle();
}

void flat::gl::Triangle::releaseRectangle()
{
    glDeleteVertexArrays(1,&vao);
}

/*
    flat::gl::Rectangle
*/

flat::gl::Rectangle::Rectangle()
    : vao(0),vbo(0),ebo(0)
{
}

flat::gl::Rectangle::~Rectangle()
{
    releaseRectangle();
}

void flat::gl::Rectangle::releaseRectangle()
{
    glDeleteVertexArrays(1,&vao);
}
