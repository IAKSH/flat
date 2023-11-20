#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

quick3d::test::Application::Application(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept
	: context(title, window_w, window_h)
{
}

void quick3d::test::Application::record_delta_time() noexcept
{
	double now_time = glfwGetTime();
	delta_sec = last_recored_time - now_time;
	last_recored_time = now_time;
}

void quick3d::test::Application::run() noexcept
{
	try
	{
		while (!glfwWindowShouldClose(glfwGetCurrentContext()))
		{
			record_delta_time();
			do_tick();
		}
	}
	catch (std::exception& e)
	{
		spdlog::critical("exception when Application::run()!\n{}", e.what());
	}
}

void quick3d::test::Application::do_tick() noexcept(false)
{
	glfwPollEvents();
}