#include <ecs_test/pipeline.hpp>

quick3d::test::Pass::Pass(__Pipeline<Pass>& pipeline) noexcept
	: pipeline(pipeline)
{
}
