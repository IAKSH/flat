#include "menu.hpp"

int main()
{
	ni::core::Application::getInstance().pushLayer(std::make_unique<Flat::MenuLayer>());
	ni::core::Application::getInstance().run();
}