#include <memory>
#include <iostream>

#include "glfw_window.hpp"

int main()
{
    std::unique_ptr<flat::Window> window = std::make_unique<flat::FWWindow>();
    window->initWindow();
    window->setWindowWidth(720);
    window->setWindowTitle("hello world!");
    window->bindContext();

    while(true)
    {
        window->setWindowPosition(1000,500);

        window->updateWindow();
        std::cout << std::endl;
        std::cout << "x:" << window->getWindowPositionX() << '\n';
        std::cout << "y:" << window->getWindowPositionY() << '\n';
        std::cout << "w:" << window->getWindowWidth() << '\n';
        std::cout << "h:" << window->getWindowHeight() << '\n';
    }

    return 0;
}