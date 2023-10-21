#include <quick_core/com_reverberator.hpp>

quick3d::al::Source& quick3d::core::Reverberator::get_source() noexcept
{
	return source;
}

void quick3d::core::Reverberator::on_tick(float delta_ms) noexcept(false)
{
}
