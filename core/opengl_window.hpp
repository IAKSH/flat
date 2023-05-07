#pragma once

#include "window.hpp"

namespace ni::core::opengl
{
    class Window : public core::Window<Window>
	{
	private:
		GLFWwindow* win;
		std::string winName;
        std::function<void(Event&)> eventCallback;
		void initialize();
		void initializeWithoutBackends();
		void release();
		inline static bool backendsInitialized{ false };

	public:
		Window(std::string_view name);
		~Window();
		GLFWwindow* getGLFWWindow();

		void imp_update();
        void imp_onEvent(Event& e);
		void imp_setPositionX(const int& x);
		void imp_setPositionY(const int& y);
		void imp_setHeight(const int& h);
		void imp_setWidth(const int& w);
		void imp_setTitle(std::string_view title);
		void imp_setEventCallbackFunc(const std::function<void(Event&)>& func);
		int imp_getPositionX();
		int imp_getPositionY();
		int imp_getHeight();
		int imp_getWidth();
        std::string_view imp_getName();
	};
}