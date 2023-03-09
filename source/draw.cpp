#include <array>
#include <string>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "draw.hpp"

void flat::Drawmeta::createVBO()
{
	auto x = getPosX();
	auto y = getPosY();
	auto hh = getSizeH() / 2.0f;
	auto hw = getSizeW() / 2.0f;

	float vertices[]{
		hw, hh, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		hw, -1.0f * hh, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-1.0f * hw, -1.0f * hh, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * hw, hh, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f};

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void flat::Drawmeta::createEBO()
{
	const uint32_t indices[] =
		{
			0, 1, 3,
			1, 3, 2};

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void flat::Drawmeta::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, curretnAnimation->get()->getBufferId());
	tryUpdateAnimation();
}

void flat::Drawmeta::tryUpdateAnimation()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastAnimationUpdate).count() >= currentAnimationInterval)
	{
		lastAnimationUpdate = std::chrono::steady_clock::now();
		if (curretnAnimation + 1 != currentAnimations->end())
			curretnAnimation++;
		else
			curretnAnimation = currentAnimations->begin();
	}
}

flat::Drawmeta::Drawmeta()
{
}

flat::Drawmeta::~Drawmeta()
{
}

void flat::Drawmeta::loadNewAnimation(std::string_view name, uint32_t ms, std::initializer_list<std::string_view> &&pathes)
{
	auto count = pathes.size();
	std::vector<std::shared_ptr<Texture>> container;
	// container->resize(count);
	uint32_t tempBufferId;

	for (int i = 0; i < count; i++)
	{
		glGenTextures(1, &tempBufferId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int w, h, channels;
		unsigned char *data;

		data = stbi_load((pathes.begin() + i)->data(), &w, &h, &channels, 0);
		if (!data)
		{
			std::cerr << "[ERROR] Can't load " << (pathes.begin() + i)->data() << std::endl;
			abort();
		}

		glBindTexture(GL_TEXTURE_2D, tempBufferId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		container.push_back(std::make_shared<Texture>(tempBufferId, data, static_cast<size_t>(w * h * channels * sizeof(char))));
	}

	animations[std::string(name)] = std::pair<uint32_t, decltype(container)>(ms, container);
}

void flat::Drawmeta::removeAnimation(std::string_view name)
{
	animations.erase(std::string(name));
}

void flat::Drawmeta::loadAnimation(std::string_view name)
{
	auto it = animations.find(std::string(name));
	if (it == animations.end())
	{
		std::cerr << "[ERROR] can't find animation \"" << name << "\"" << std::endl;
		abort();
	}

	currentAnimations = &it->second.second;
	currentAnimationInterval = it->second.first;
	curretnAnimation = currentAnimations->begin();
	lastAnimationUpdate = std::chrono::steady_clock::now();
}

void flat::Drawmeta::setTexOffset(const glm::vec2& offset)
{
	texOffset = offset;
}

void flat::Drawmeta::addTexOffset(const glm::vec2& offset)
{
	texOffset += offset;
}

glm::vec2 flat::Drawmeta::getTexOffset()
{
	return texOffset;
}

size_t flat::Drawmeta::getAnimationCount()
{
	return size_t();
}

void flat::Drawmeta::makeDrawMeta()
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	createVBO();
	createEBO();

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

void flat::Drawmeta::makeDrawMeta(std::array<float, 8> &texCoords, std::array<float, 12> &colors)
{
}

void flat::Drawmeta::drawMeta()
{
	glBindVertexArray(vaoId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void flat::Drawmeta::draw()
{
	useTexture();
	drawMeta();
}

void flat::Painter::initializeGLFW()
{
	glfwInit();
	glfwInitHint(GLFW_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Hello OpenGL!", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "[ERROR] Can't create window" << std::endl;
		abort();
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(3);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
								   { glViewport(0, 0, width, height); });
}

void flat::Painter::initializeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "[ERROR] Can't get OpenGL address" << std::endl;
		abort();
	}
}

void flat::Painter::initializeShader()
{
	shaderId = glCreateProgram();
	uint32_t vertexShaderId = createVShader();
	uint32_t fragmentShaderId = createFShader();

	glAttachShader(shaderId, vertexShaderId);
	glAttachShader(shaderId, fragmentShaderId);
	glLinkProgram(shaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	glUseProgram(shaderId);
	glUniform1i(glGetUniformLocation(shaderId, "texture0"), 0); // "texture0" -> GL_TEXTURE0
																// glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 1);// "texture1" -> GL_TEXTURE1
}

void flat::Painter::checkVShader(uint32_t vshader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vshader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "[ERROR] Failed to compile vertex shader: " << infoLog << std::endl;
		abort();
	}
}

void flat::Painter::checkFShader(uint32_t fshader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fshader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "[ERROR] Failed to compile fragment shader: " << infoLog << std::endl;
		abort();
	}
}

uint32_t flat::Painter::createVShader()
{
	const char *source = vertexSource.c_str();
	uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &source, nullptr);
	glCompileShader(vertexShaderId);
	return vertexShaderId;
}

uint32_t flat::Painter::createFShader()
{
	const char *source = fragmentSource.c_str();
	uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &source, nullptr);
	glCompileShader(fragmentShaderId);
	return fragmentShaderId;
}

flat::Painter::Painter()
{
}

flat::Painter::~Painter()
{
}

void flat::Painter::initializePainter()
{
	if (!window)
	{
		initializeGLFW();
		initializeGLAD();
		initializeShader();
	}
}

void flat::Painter::setFShaderSource(std::string source)
{
	fragmentSource = source;
}

void flat::Painter::setVShaderSource(std::string source)
{
	vertexSource = source;
}

GLFWwindow *flat::Painter::getWindow()
{
	return window;
}

uint32_t flat::Painter::getShaderId()
{
	return shaderId;
}

flat::Texture::Texture(uint32_t id, unsigned char *data, size_t length)
{
	auto pair = std::pair(data, length);
	auto it = globalTextureHashtable.find(pair);
	if (it != globalTextureHashtable.end())
		bufferId = globalTextureHashtable[pair];
	else
		bufferId = id;
}

flat::Texture::~Texture()
{
	releaseBuffer();
}

void flat::Texture::releaseBuffer()
{
	glDeleteTextures(1, &bufferId);
}

const uint32_t &flat::Texture::getBufferId()
{
	return bufferId;
}

void flat::Painter::loadFShaderFromFile(std::string_view path)
{
	std::string readinBuffer;
	std::ifstream ifs(path.data(), std::ios::in);
	if (!ifs.is_open())
	{
		std::cerr << "[ERROR] can't open " << path << std::endl;
		abort();
	}

	fragmentSource = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	ifs.close();
}

void flat::Painter::loadVShaderFromFile(std::string_view path)
{
	std::string readinBuffer;
	std::ifstream ifs(path.data(), std::ios::in);
	if (!ifs.is_open())
	{
		std::cerr << "[ERROR] can't open " << path << std::endl;
		abort();
	}

	vertexSource = std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	ifs.close();
}

void flat::Painter::setTransfrom(const glm::mat4 &trans)
{
	auto location = glGetUniformLocation(shaderId, "trans");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));
}

void flat::Painter::setTexOffset(const glm::vec2 &offset)
{
	auto location = glGetUniformLocation(shaderId, "texOffset");
	glUniform2fv(location,1,glm::value_ptr(offset));
}
