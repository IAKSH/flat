#include <quick_ecs/ecs.hpp>

void quick3d::ecs::System::system_run() noexcept
{
	running = true;
}

void quick3d::ecs::System::system_stop() noexcept
{
	running = false;
}

bool quick3d::ecs::System::is_running() noexcept
{
	return running;
}