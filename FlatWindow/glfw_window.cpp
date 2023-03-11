#include "glfw_window.hpp"

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
    "   //if(texColor.a < 0.1)\n"
    "   //    discard;\n"
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
}

void flat::gl::FWWindow::drawTriangle(const flat::Triangle &triangle)
{
    // TODO
}

void flat::gl::FWWindow::makeupTriangle(flat::Triangle *triangle)
{
    // TODO
}

void flat::gl::FWWindow::makeupRectangle(flat::Rectangle *rectangle)
{
    // TODO
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
    glUniformMatrix4fv(glGetUniformLocation(shaderId,uniform.data()),1,false,glm::value_ptr(mat));
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
