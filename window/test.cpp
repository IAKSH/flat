#include <memory>
#include <iostream>

#include "glfw_window.hpp"

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

    while(true)
    {
        if(kbInput.checkKeyboardDown(GLFW_KEY_ESCAPE))
            break;

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