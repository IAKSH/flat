#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>

namespace flat
{
    class Window
    {
    private:
        GLFWwindow* win;
        std::string name;
    };
}