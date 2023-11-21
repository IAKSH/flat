#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

int main() noexcept
{
	spdlog::set_level(spdlog::level::debug);
	quick3d::test::Application app;

	auto window_layer1{ app.add_layer<quick3d::test::ImGuiWindowLayer>("cppoes: new entity architecture test", 800, 600) };
	auto window_layer2{ app.add_layer<quick3d::test::ImGuiWindowLayer>("multi-window test", 1280, 700) };
	app.add_layer<quick3d::test::OESLayer>(window_layer1->get_window());
	app.add_layer<quick3d::test::OESLayer>(window_layer2->get_window());
	app.add_layer<quick3d::test::ImGuiLayer>(*window_layer1, "window1 debug");
	//app.add_layer<quick3d::test::ImGuiLayer>(*window_layer2, "window2 debug");

	auto window_update_layer{ app.add_layer<quick3d::test::WindowUpdateLayer>() };
	window_update_layer->add_window(window_layer1->get_window());
	window_update_layer->add_window(window_layer2->get_window());

	app.exec();
	return 0;
}