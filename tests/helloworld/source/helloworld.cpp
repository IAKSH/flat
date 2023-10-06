#include <iostream>
#include <quick_gl/context.hpp>

using namespace quick3d::gl;

int main() noexcept
{
    try
    {
        Context context("你好",800,600);

        auto win{ context.get_window(0).get_glfw_window() };
        while(!glfwWindowShouldClose(win))
        {
            glfwSwapBuffers(win);
            glfwPollEvents();
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        std::terminate();
    }
}