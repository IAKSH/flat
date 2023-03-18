#pragma once

#include "abstruct_api.hpp"
#include "initialized.hpp"

#include <algorithm>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glfwms
{
    class MouseSource : public msapi::MouseSource<MouseSource>
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
            if(window == nullptr)
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
            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                abort();
            }
        }

    public:
        MouseSource()
        {
            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glfw") == std::end(init::initialized))
            {
                std::cerr << "warning: init window by keyboard input modules" << std::endl;
                initGLFW();
                init::initialized.push_back("glfw");
            }
            else
                window = glfwGetCurrentContext();

            if(std::find(std::begin(init::initialized), std::end(init::initialized), "glad") == std::end(init::initialized))
            {
                initGLAD();
                init::initialized.push_back("glad");
            }
        }

        ~MouseSource() {}

        float imp_getMousePositionX()
        {
            double buffer;
            glfwGetCursorPos(window, &buffer, nullptr);
            return buffer;
        }

        float imp_getMousePositionY()
        {
            double buffer;
            glfwGetCursorPos(window, nullptr, &buffer);
            return buffer;
        }

        bool imp_checkMouseLeft()
        {
            return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
        }

        bool imp_checkMouseMiddle()
        {
            return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_MIDDLE);
        }

        bool imp_checkMouseRight()
        {
            return glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT);
        }
    };
}  // namespace glfwms