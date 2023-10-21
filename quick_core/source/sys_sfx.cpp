#include <quick_core/sys_sfx.hpp>

quick3d::core::SFXSystem::SFXSystem() noexcept(false)
	: device(), context(device)
{
}

quick3d::core::SFXSystem::SFXSystem(std::string_view device_name) noexcept(false)
	: device(device_name.data()), context(device)
{
}

void quick3d::core::SFXSystem::on_tick(float delta_ms) noexcept(false)
{
}