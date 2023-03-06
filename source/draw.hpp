#pragma once

#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <memory>
#include <iostream>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics.hpp"

namespace flat
{
	struct Texture
	{
	private:
		// map<pair<data begin,length>,bufferId>
		inline static std::map<std::pair<unsigned char*,size_t>,uint32_t> globalTextureHashtable;
		uint32_t bufferId;
	public:
		Texture(uint32_t id,unsigned char* data,size_t length);
		~Texture();
		void releaseBuffer();
		const uint32_t &getBufferId();
	};

	class Drawmeta : virtual public Physical
	{
	private:
		std::map<std::string, std::pair<uint32_t, std::shared_ptr<std::vector<Texture>>>> animations;
		std::shared_ptr<std::vector<Texture>> currentAnimations;
		std::vector<Texture>::iterator curretnAnimation;
		std::chrono::steady_clock::time_point lastAnimationUpdate;
		uint32_t vboId, eboId, vaoId;
		uint32_t currentAnimationInterval;
		void createVBO();
		void createEBO();
		void drawMeta();
		void useTexture();
		void tryUpdateAnimation();

	public:
		Drawmeta();
		~Drawmeta();
		void loadNewAnimation(std::string_view name, uint32_t ms, std::initializer_list<std::string_view> &&pathes);
		void removeAnimation(std::string_view name);
		void loadAnimation(std::string_view name);
		size_t getAnimationCount();
		void makeDrawMeta();
		void makeDrawMeta(std::array<float, 8> &texCoords, std::array<float, 12> &colors);
		void draw();
	};

	class Painter
	{
	private:
		uint32_t shaderId;
		GLFWwindow *window;
		std::string vertexSource, fragmentSource;
		void initializeGLFW();
		void initializeGLAD();
		void checkVShader(uint32_t vshader);
		void checkFShader(uint32_t fshader);
		uint32_t createVShader();
		uint32_t createFShader();
		void initializeShader();

	protected:
		uint32_t getShaderId();
		void setTransfrom(glm::mat4 &trans);
		void setTransfrom(glm::mat4 &&trans);
		template <typename T>
		void setUniform(std::string_view uniform, std::initializer_list<T> vals)
		{
			static_assert(std::is_same<T, int>::value || std::is_same<T, unsigned int>::value || std::is_same<T, float>::value);

			auto reportTypeError = [&]()
			{ std::cerr << "[ERROR] flat::Shader::write | wrong type: typeid(T).name() = " << typeid(T).name() << std::endl; };

			auto location = glGetUniformLocation(shaderId, uniform.data());
			int len = 0;
			for (auto &item : vals)
				len++;

			switch (len)
			{
			case 1:
				if (std::is_same<T, int>::value)
					glUniform1i(location, *vals.begin());
				else if (std::is_same<T, unsigned int>::value)
					glUniform1ui(location, *vals.begin());
				else if (std::is_same<T, float>::value)
					glUniform1f(location, *vals.begin());
				else
					reportTypeError();
				break;
			case 2:
				if (std::is_same<T, int>::value)
					glUniform2i(location, *vals.begin(), *(vals.begin() + 1));
				else if (std::is_same<T, unsigned int>::value)
					glUniform2ui(location, *vals.begin(), *(vals.begin() + 1));
				else if (std::is_same<T, float>::value)
					glUniform2f(location, *vals.begin(), *(vals.begin() + 1));
				else
					reportTypeError();
				break;
			case 3:
				if (std::is_same<T, int>::value)
					glUniform3i(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2));
				else if (std::is_same<T, unsigned int>::value)
					glUniform3ui(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2));
				else if (std::is_same<T, float>::value)
					glUniform3f(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2));
				else
					reportTypeError();
				break;
			case 4:
				if (std::is_same<T, int>::value)
					glUniform4i(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2), *(vals.begin() + 3));
				else if (std::is_same<T, unsigned int>::value)
					glUniform4ui(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2), *(vals.begin() + 3));
				else if (std::is_same<T, float>::value)
					glUniform4f(location, *vals.begin(), *(vals.begin() + 1), *(vals.begin() + 2), *(vals.begin() + 3));
				else
					reportTypeError();
				break;
			default:
				std::cerr << "[ERROR] flat::Shader::writeUniformInt | too many/few parameter (unsgined int * " << len << std::endl;
				abort();
			}
		}

	public:
		Painter();
		~Painter();
		void initializePainter();
		void setFShaderSource(std::string source);
		void setVShaderSource(std::string source);
		void loadFShaderFromFile(std::string_view path);
		void loadVShaderFromFile(std::string_view path);
		GLFWwindow *getWindow();
	};
}