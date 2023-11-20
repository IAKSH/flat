#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

int main() noexcept
{
	spdlog::set_level(spdlog::level::debug);
	quick3d::test::Application("cppoes: new entity architecture test", 800, 600).run();
	return 0;
}