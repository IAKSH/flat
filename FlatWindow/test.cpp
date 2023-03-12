#include <memory>
#include <iostream>

#include "flat_gl/window.hpp"

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

    flat::RGBAColor color;
    color.r = 1.0f;
    color.g = 0.0f;
    color.b = 0.0f;
    color.a = 0.5f;

    std::cout << glfwGetVersionString() << std::endl;

    flat::gl::Texture _texture;
    flat::Texture& texture = _texture;
    texture.initTexture();
    texture.loadTextureFromFile("D:/Programming-Playground/flat2/demo/images/test.png");

    flat::gl::Rectangle _rect;
    flat::Rectangle& rect = _rect;
    rect.w = 0.75f;
    rect.x = 0.5f;
    rect.colors[0].r = 0.8f;
    rect.colors[0].a = 0.5f;
    rect.colors[1].r = 0.8f;
    rect.colors[1].a = 0.5f;
    rect.colors[2].b = 0.8f;
    rect.colors[2].a = 0.5f;
    rect.colors[3].r = 0.8f;
    rect.colors[3].a = 0.5f;

    renderer.makeupRectangle(&rect);

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;

        renderer.cleanScreen(color);
        renderer.bindTexture(0, texture);
        renderer.drawRectangle(rect);

        rect.rotateX += 0.01f;
        rect.rotateY += 0.0025f;
        rect.rotateZ += 0.005f;

        window.setWindowPosition(1000,500);
        window.updateWindow();

        if(msInput.checkMouseLeft())
        {
            std::cout << "mouse x:" << msInput.getMousePosX() << '\n';
            std::cout << "mouse y:" << msInput.getMousePosY() << '\n';
        }
        else if(msInput.checkMouseRight())
        {
            std::cout << std::endl;
            std::cout << "x:" << window.getWindowPositionX() << '\n';
            std::cout << "y:" << window.getWindowPositionY() << '\n';
            std::cout << "w:" << window.getWindowWidth() << '\n';
            std::cout << "h:" << window.getWindowHeight() << '\n';
        }
        else if(msInput.checkMouseMiddle())
            std::cout << "Hello world!" << std::endl;
    }

    window.destroyWindow();
    return 0;
}