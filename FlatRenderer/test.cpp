#include "gl_renderer.hpp"
#include "glfw_window.hpp"

#include <array>
#include <iostream>

int main()
{
    flat::FWWindow glfwWindow;
    flat::Window& window = glfwWindow;
    flat::KeyboardInputSource& kbInput = glfwWindow;
    flat::MouseInputSource& msInput = glfwWindow;

    window.initWindow();
    window.setWindowWidth(720);
    window.setWindowTitle("hello world!");
    window.bindContext();

    flat::glcore::Renderer _renderer;
    flat::Renderer& renderer = _renderer;
    renderer.initRenderer();
    flat::RGBAColor color;
    color.a = 1.0f;
    color.g = 0.0f;
    color.b = 0.0f;
    color.a = 0.5f;

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;

        window.setWindowPosition(1000,500);
        window.updateWindow();

        renderer.cleanScreen(color);
    }

    window.destroyWindow();

    return 0;
}