#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "event.hpp"

namespace flat::core
{
	class Window
	{
	private:
		GLFWwindow* win;
		std::string winName;
		void initialize();
		void initializeWithoutBackends();
		void release();
		inline static bool backendsInitialized{ false };

	public:
		Window(std::string_view name);
		~Window();
		GLFWwindow* getGLFWWindow();
		void update();
		void setPositionX(int x);
		void setPositionY(int y);
		void setHeight(int h);
		void setWidth(int w);
		void setTitle(std::string_view title);
		void setEventCallbackFunc(const std::function<void(Event&)>& func);
		int getPositionX();
		int getPositionY();
		int getHeight();
		int getWidth();

		struct Callback
		{
			std::function<void(Event&)> func;
		} callback;
	};
}