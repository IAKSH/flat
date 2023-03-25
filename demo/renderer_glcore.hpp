#pragma once

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <memory>

#include "renderer.hpp"
#include "initialized.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <freetype/freetype.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace flat::imp::renderer::glcore
{
	class Texture : public flat::Texture
	{
	private:
		uint32_t textureId;

	public:
		Texture(uint32_t id) : textureId(id) {}
		virtual ~Texture() override { glDeleteTextures(1, &textureId); }
		uint32_t getTextureId() { return textureId; }
	};

	class Font : public flat::Font
	{
	private:
		std::unordered_map<char, std::unique_ptr<Texture>> textures;
		int fontSize;

	public:
		Font() : fontSize(0)
		{}
		virtual ~Font() override {}

		int getFontSize()
		{
			return fontSize;
		}

		void setFontSize(int size)
		{
			fontSize = size;
		}

		void addTexture(char c, int texId)
		{
			if (textures.count(c) != 0)
			{
				std::cerr << "error: texture conflict in Font, c = " << '\'' << c << '\'' << std::endl;
				abort();
			}

			textures[c] = std::move(std::make_unique<Texture>(texId));
		}

		flat::Texture& operator() (char c) override
		{
			if (textures.count(c) == 0)
			{
				std::cerr << "error: can't find texture \'" << c << "\' from Font" << std::endl;
				abort();
			}

			return *textures[c];
		}
	};

	class Renderer : public flat::Renderer<Renderer>
	{
	private:
		uint32_t vao, vbo, ebo, shader;

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec2 aTexCoord;\n"
			"out vec4 aColor;\n"
			"out vec2 aTexCoordOut;\n"
			"uniform mat4 transform;\n"
			"uniform vec2 texOffset;\n"
			"uniform vec2 texScale;\n"
			"uniform vec4 color;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = transform * vec4(aPos, 1.0f);\n"
			"    aColor = color;\n"
			"    aTexCoordOut = (vec2(aTexCoord.x + texOffset.x, 1.0 - aTexCoord.y + texOffset.y) * texScale) + texOffset;\n"
			"}\0";

		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec4 aColor;\n"
			"in vec2 aTexCoordOut;\n"
			"uniform sampler2D texture0;\n"
			"void main()\n"
			"{\n"
			"    vec4 texColor = texture(texture0,aTexCoordOut);\n"
			"    if(texColor.a < 0.1)\n"
			"        discard;\n"
			"    FragColor = texColor * aColor;\n"
			"}\n\0";

		void initGLFW()
		{
			std::cerr << "warnning: glfw initialized by Renderer" << std::endl;

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			GLFWwindow* window = glfwCreateWindow(800, 600, "FLAT", NULL, NULL);
			if (window == NULL)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				abort();
			}
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
		}

		void initGLAD()
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				abort();
			}
		}

		void initShader()
		{
			unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(vertexShader);
			// check for shader compile errors
			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cout << "error: vertex shader compilation failed\n" << infoLog << std::endl;
			}
			// fragment shader
			unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(fragmentShader);
			// check for shader compile errors
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				std::cout << "error: fragment shader compilation failed\n" << infoLog << std::endl;
			}
			// link shaders
			shader = glCreateProgram();
			glAttachShader(shader, vertexShader);
			glAttachShader(shader, fragmentShader);
			glLinkProgram(shader);
			// check for linking errors
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 512, NULL, infoLog);
				std::cout << "error: can't link shader\n" << infoLog << std::endl;
			}
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			glUseProgram(shader);
			glUniform1i(glGetUniformLocation(shader, "texture0"), 0);
		}

		void makeDrawMeta()
		{
			float vertices[] = {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f, 0.0f, 1.0f   // top left
			};
			unsigned int indices[] = {
				0, 1, 3,  // first Triangle
				1, 2, 3   // second Triangle
			};
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);
			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// texture coord attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

	public:
		Renderer() : vao(0), vbo(0), ebo(0)
		{
			imp_initialize();
		}

		~Renderer()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteProgram(shader);
		}

		void imp_drawRectangle(flat::Rectangle& rectangle)
		{
			glm::mat4 trans(1.0f);
			trans *= glm::translate(glm::mat4(1.0f), glm::vec3(rectangle.getX(), rectangle.getY(), rectangle.getZ()));
			trans *= glm::scale(glm::mat4(1.0f), glm::vec3(rectangle.getWidth(), rectangle.getHeight(), 1.0f));
			trans *= glm::rotate(glm::mat4(1.0f), glm::radians(rectangle.getRotateZ()), glm::vec3(0.0f, 0.0f, 1.0f));

			unsigned int location = glGetUniformLocation(shader, "transform");
			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));

			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

		void imp_setColor(flat::Color& color)
		{
			unsigned int location = glGetUniformLocation(shader, "color");
			glUniform4f(location, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
		}

		void imp_initialize()
		{

			if (std::find(std::begin(flat::initialized), std::end(flat::initialized), "glfw") == std::end(flat::initialized))
			{
				initGLFW();
				flat::initialized.push_back("glfw");
			}

			if (std::find(std::begin(flat::initialized), std::end(flat::initialized), "glad") == std::end(flat::initialized))
			{
				initGLAD();
				flat::initialized.push_back("glad");
			}

			initShader();
			makeDrawMeta();
		}

		void imp_bindTexture(flat::Texture& texture)
		{
			if (typeid(texture) != typeid(Texture))
			{
				std::cerr << "error: wrong texture type" << std::endl;
				abort();
			}

			Texture& tex = (Texture&)texture;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex.getTextureId());
		}

		void imp_setTextureOffset(flat::TextureOffset& offset)
		{
			unsigned int texOffset = glGetUniformLocation(shader, "texOffset");
			glUniform2f(texOffset, offset.getOffsetX(), offset.getOffsetY());

			unsigned int texScale = glGetUniformLocation(shader, "texScale");
			glUniform2f(texScale, offset.getScaleX(), offset.getScaleY());
		}

		std::unique_ptr<flat::Texture> imp_genTexture(std::string_view path)
		{
			uint32_t textureId;
			glGenTextures(1, &textureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int w, h, channels;
			unsigned char* data;

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
			return std::make_unique<Texture>(textureId);
		}

		std::unique_ptr<Font> imp_genFont(std::string_view path)
		{
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				std::cout << "error: could not init FreeType Library" << std::endl;

			FT_Face face;
			if (FT_New_Face(ft, path.data(), 0, &face))
				std::cout << "error: failed to load font" << std::endl;

			FT_Set_Pixel_Sizes(face, 0, 48);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // 禁用字节对齐限制

			auto font = std::make_unique<Font>();

			for (GLubyte c = 0; c < 128; c++)
			{
				// 加载字符的字形
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "error: failed to load Glyph" << std::endl;
					continue;
				}

				// gen RGBA
				unsigned char* rgbaData = new unsigned char[face->glyph->bitmap.width * face->glyph->bitmap.rows * 4];
				for (int i = 0; i < face->glyph->bitmap.width * face->glyph->bitmap.rows; i++) {
					rgbaData[i * 4] = face->glyph->bitmap.buffer[i];
					rgbaData[i * 4 + 1] = face->glyph->bitmap.buffer[i];
					rgbaData[i * 4 + 2] = face->glyph->bitmap.buffer[i];
					rgbaData[i * 4 + 3] = 255;
				}

				// set every black pixel's alpha to 255
				for (int i = 0; i < face->glyph->bitmap.width * face->glyph->bitmap.rows; i++) {
					if ((rgbaData[i * 4] == 0) && (rgbaData[i * 4 + 1] == 0) && (rgbaData[i * 4 + 2] == 0)) {
						rgbaData[i * 4] = 0;
						rgbaData[i * 4 + 1] = 0;
						rgbaData[i * 4 + 2] = 0;
						rgbaData[i * 4 + 3] = 0;
					}
					else {
						rgbaData[i * 4] = rgbaData[i * 4];
						rgbaData[i * 4 + 1] = rgbaData[i * 4 + 1];
						rgbaData[i * 4 + 2] = rgbaData[i * 4 + 2];
						rgbaData[i * 4 + 3] = 255;
					}
				}

				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaData);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				font->addTexture(c, texture);
				delete[] rgbaData;
			}

			FT_Done_Face(face);
			FT_Done_FreeType(ft);

			return font;
		}
	};
}