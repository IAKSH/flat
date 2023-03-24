#pragma once

#include "initialized.hpp"
#include "keyboard.hpp"

#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace flat::imp::keyboard::glfw
{
	class KeyboardSource : public flat::KeyboardSource<KeyboardSource>
	{
	private:
		GLFWwindow* window;
		void initGLFW()
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(800, 600, "FLAT", nullptr, nullptr);
			if (window == nullptr)
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

	public:
		KeyboardSource()
		{
			if (std::find(std::begin(flat::initialized), std::end(flat::initialized), "glfw") == std::end(flat::initialized))
			{
				std::cerr << "warning: init window by keyboard input modules" << std::endl;
				initGLFW();
				flat::initialized.push_back("glfw");
			}
			else
				window = glfwGetCurrentContext();

			if (std::find(std::begin(flat::initialized), std::end(flat::initialized), "glad") == std::end(flat::initialized))
			{
				initGLAD();
				flat::initialized.push_back("glad");
			}
		}

		~KeyboardSource() {}
		bool imp_checkKey(int code) { return glfwGetKey(window, code) == GLFW_PRESS; }
	};
}  // namespace glfwkb