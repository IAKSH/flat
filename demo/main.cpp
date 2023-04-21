#include "menu.hpp"

int main()
{
    ni::core::Application app;
	app.pushLayer(std::make_unique<Flat::MenuLayer>());
	app.run();
}