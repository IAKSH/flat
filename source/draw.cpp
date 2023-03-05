#include <array>
#include <iostream>

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
}

#include "draw.hpp"

void flat::Drawmeta::createVBO()
{
	auto x = getPosX();
	auto y = getPosY();
	auto hh = getSizeH() / 2.0f;
	auto hw = getSizeW() / 2.0f;

	//float vertexes[]{x - hw,y + hh,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,x + hw,y + hh,0.0f,x + hw,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f ,y - hh,0.0f,x - hw,y - hh,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f};
	
	// for test
	float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void flat::Drawmeta::createEBO()
{
	const uint32_t indices[] =
	{
		0, 1, 3,
		1, 3, 2
	};

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void flat::Drawmeta::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, curretnAnimation->id);
	tryUpdateAnimation();
}

void flat::Drawmeta::tryUpdateAnimation()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastAnimationUpdate).count() >= currentAnimationInterval)
	{
		lastAnimationUpdate = std::chrono::steady_clock::now();
		if (curretnAnimation != currentAnimations->end())
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
	std::shared_ptr<std::vector<Texture>> container = std::make_shared<std::vector<Texture>>();
	container->resize(count);

	stbi_set_flip_vertically_on_load(true);

	for (auto item : pathes)
	{
		glGenTextures(count, &(container->data()->id));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int w, h, channels;
		unsigned char *data;
		for (int i = 0; i < count; i++)
		{
			data = stbi_load((pathes.begin() + i)->data(), &w, &h, &channels, 0);
			if (!data)
			{
				std::cerr << "[ERROR] Can't load " << (pathes.begin() + i)->data() << std::endl;
				abort();
			}

			glBindTexture(GL_TEXTURE_2D, container->data()->id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
	}

	animations[std::string(name)] = std::pair<uint32_t, std::shared_ptr<std::vector<Texture>>>(ms,container);
}

void flat::Drawmeta::removeAnimation(std::string_view name)
{
	animations.erase(std::string(name));
}

void flat::Drawmeta::loadAnimation(std::string_view name)
{
	auto it = animations.find(std::string(name));
	if(it == animations.end())
	{
		std::cerr << "[ERROR] can't find animation \"" << name << "\"" << std::endl;
		abort();
	}

	currentAnimations = it->second.second;
	currentAnimationInterval = it->second.first;
	curretnAnimation = it->second.second->begin();
	lastAnimationUpdate = std::chrono::steady_clock::now();
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
	uint32_t shaderId = glCreateProgram();
	uint32_t vertexShaderId = createVShader();
	uint32_t fragmentShaderId = createFShader();

	glAttachShader(shaderId, vertexShaderId);
	glAttachShader(shaderId, fragmentShaderId);
	glLinkProgram(shaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
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
	initializeGLFW();
	initializeGLAD();
	initializeShader();
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

flat::Texture::~Texture()
{
	glDeleteTextures(1, &id);
}