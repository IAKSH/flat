#include <quick_gl/pipeline.hpp>

quick3d::gl::Pass::Pass(__Pipeline<Pass>& pipeline) noexcept
	: pipeline(pipeline)
{
}
