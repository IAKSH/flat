#include <memory>
#include <iostream>

#include <flat_gl/window.hpp>
#include "GLFW/glfw3.h"
#include "flat_gjk/gjk.hpp"

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

    flat::gl::Texture _texture;
    flat::Texture& texture = _texture;
    texture.initTexture();
    texture.loadTextureFromFile("D:/Programming-Playground/flat2/demo/images/test.png");

    flat::gl::Rectangle _rect;
    flat::gl::Rectangle _rect1;
    flat::Rectangle& rect = _rect;
    flat::Rectangle& rect1 = _rect1;
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

    rect1.w = 0.25;
    rect1.h = 1.0f;
    rect1.x = 0.0f;
    rect1.colors[0].r = 0.8f;
    rect1.colors[0].a = 0.5f;
    rect1.colors[1].r = 0.8f;
    rect1.colors[1].a = 0.5f;
    rect1.colors[2].b = 0.8f;
    rect1.colors[2].a = 0.5f;
    rect1.colors[3].r = 0.8f;
    rect1.colors[3].a = 0.5f;

    flat::gjk::Hitbox2D _hitbox0;
    flat::gjk::Hitbox2D _hitbox1;
    flat::Hitbox2D& hitbox0 = _hitbox0;
    flat::Hitbox2D& hitbox1 = _hitbox1;

    hitbox0.setHeight(rect.h);
    hitbox0.setWidth(rect.w);

    hitbox1.setHeight(rect1.h);
    hitbox1.setWidth(rect1.w);

    renderer.makeupRectangle(&rect);
    renderer.makeupRectangle(&rect1);

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;
        if(kbInput.checkKeyboardDown(GLFW_KEY_D))
            rect.x += 0.01f;
        if(kbInput.checkKeyboardDown(GLFW_KEY_A))
            rect.x -= 0.01f;

        //rect.rotateX += 0.01f;
        //rect.rotateY += 0.0025f;
        //rect.rotateZ += 0.005f;

        rect1.rotateZ += 0.0025f;

        // 同步Hitbox，实际上这一步应该是在Gameobject中完成
        hitbox0.setPosX(rect.x);
        hitbox0.setPosY(rect.y);
        hitbox0.setRotate(rect.rotateZ);

        hitbox1.setPosX(rect1.x);
        hitbox1.setPosY(rect1.y);
        hitbox1.setRotate(rect1.rotateZ);

        if(hitbox0.checkHit(hitbox1))
            std::cout << "hit!\n";

        renderer.cleanScreen(color);
        renderer.bindTexture(0, texture);
        renderer.drawRectangle(rect);
        renderer.drawRectangle(rect1);

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