#include <quick_core/entity.hpp>

quick3d::core::System::System() noexcept
	: running(true)
{
}

bool quick3d::core::System::is_running() noexcept
{
	return running;
}

quick3d::core::Entity::Entity(__EntityManager<Entity>& manager) noexcept
	: entity_manager(manager)
{
}