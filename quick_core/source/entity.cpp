#include <quick_core/entity.hpp>

void quick3d::core::Entity::bind_component(Component* com) noexcept
{
	components.push_back(com);
}

void on_tick() noexcept
{

}

void quick3d::core::Entity::on_tick(float delta_ms) noexcept(false)
{
	for (auto& com : components)
		com->on_tick(delta_ms);
}

quick3d::core::System::System() noexcept
	: running(true)
{
}

bool quick3d::core::System::is_running() noexcept
{
	return running;
}