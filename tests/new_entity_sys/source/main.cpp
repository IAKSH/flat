#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

int main() noexcept
{
	spdlog::set_level(spdlog::level::debug);
	quick3d::test::Application app;
	auto oes_layer1{ app.add_layer<quick3d::test::OESLayer>("cppoes: new entity architecture test", 800, 600) };
	auto oes_layer2{ app.add_layer<quick3d::test::OESLayer>("multi-window test", 1280, 700) };

	app.add_layer<quick3d::test::DebugImGuiLayer>();

	auto window_update_layer{ app.add_layer<quick3d::test::WindowUpdateLayer>() };
	window_update_layer->add_context(oes_layer1->get_window());
	window_update_layer->add_context(oes_layer2->get_window());

	app.exec();
	return 0;
}