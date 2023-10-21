#include <quick_ecs/sys_sfx.hpp>

quick3d::ecs::SfxSystem::SfxSystem() noexcept
    : context(device)
{
    on_create();
}

quick3d::ecs::SfxSystem::SfxSystem(std::string_view device_name) noexcept
    : device(device_name.data()), context(device)
{
    on_create();
}

quick3d::ecs::SfxSystem::~SfxSystem() noexcept
{
    on_destroy();
}

void quick3d::ecs::SfxSystem::on_attach() noexcept(false)
{
    system_run();
}

void quick3d::ecs::SfxSystem::on_disattach() noexcept(false)
{
    system_stop();
}

void quick3d::ecs::SfxSystem::on_create() noexcept(false)
{

}

void quick3d::ecs::SfxSystem::on_destroy() noexcept(false)
{

}

void quick3d::ecs::SfxSystem::on_tick(float delta_ms) noexcept(false)
{
}