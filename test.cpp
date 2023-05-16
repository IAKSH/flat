#include <iostream>
#include "Core/application.hpp"

int main()
{
    std::cout << "hello world!\n";
    flat::Application::get_instance().run();
}