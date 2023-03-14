#include <memory>
#include <iostream>
#include <utility>

#include "flat_gl/window.hpp"
#include "flat_gl/glcore_renderer.hpp"

int main()
{
    flat::gl::FWWindow glfwWindow;
    flat::Window& window = glfwWindow;
    flat::KeyboardInputSource& kbInput = glfwWindow;
    flat::MouseInputSource& msInput = glfwWindow;
    flat::Renderer& renderer  = glfwWindow;

    window.initWindow();
    window.setWindowWidth(720);
    window.setWindowTitle("hello world!");

    dggen::Renderer<glcore::Renderer>&& ren = glcore::Renderer();
    auto birdTex = ren.genTexture("../../demo/images/bird0_1.png");

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;

        ren << birdTex << dggen::Rectangle(0.5f,0.5f,0.0f,0.5f,0.2f,0.0f,0.0f,0.2f) << std::move(dggen::flush);
        //ren << birdTex;


        std::cout << "wdnmd";

        window.updateWindow();
    }

    window.destroyWindow();
    return 0;
}