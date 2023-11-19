#include <new_entity_sys/application.hpp>

quick3d::test::Application::Application(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept
	: context(title, window_w, window_h)
{
}

void quick3d::test::Application::run() noexcept
{
	while (!glfwWindowShouldClose(glfwGetCurrentContext()))
	{

	}
}