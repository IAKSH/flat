#include <quick_ecs/com_reverberator.hpp>

quick3d::ecs::Reverberator::Reverberator() noexcept
{
	on_create();
}

quick3d::ecs::Reverberator::~Reverberator() noexcept
{
	on_destroy();
}

void quick3d::ecs::Reverberator::on_create() noexcept(false)
{

}

void quick3d::ecs::Reverberator::on_destroy() noexcept(false)
{

}

void quick3d::ecs::Reverberator::on_attach() noexcept(false)
{

}

void quick3d::ecs::Reverberator::on_disattach() noexcept(false)
{

}

void quick3d::ecs::Reverberator::on_tick(float delta_ms) noexcept(false)
{

}