#pragma once

#include "initialized.hpp"
#include "abstruct_api.hpp"

#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glfwkb
{
    class KeyboardSource : public kbapi::KeyboardSource<KeyboardSource>
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
        KeyboardSource()
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

        ~KeyboardSource() {}
        bool imp_checkKey(int code) { return glfwGetKey(window,code) == GLFW_PRESS; }
    };
}  // namespace glfwkb