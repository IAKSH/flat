#include <ecs_test/light_ball.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../tests/fine_light/model";

void quick3d::test::LightBallRenderer::setup_color_data(int index) noexcept
{
	ssbo_color.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<ColorData*>(data) };
		ptr->color[index] = glm::vec4(
			abs(move_direction_dis(gen)),
			abs(move_direction_dis(gen)),
			abs(move_direction_dis(gen)),
			1.0f
		);
	});
}

void quick3d::test::LightBallRenderer::setup_model_data(int index) noexcept
{
	auto scale_factor{ 0.0001f };
	auto scale{ glm::scale(glm::mat4(1.0f), glm::vec3(scale_factor, scale_factor, scale_factor)) };
	auto scaled_position{ scale_factor * glm::vec3(position_dis(gen), position_dis(gen) + 20.0f, position_dis(gen)) };
	ssbo_position.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<PositionData*>(data) };
		ptr->position[index] =  glm::vec4(scaled_position.r, scaled_position.g, scaled_position.b, 1.0f);
	});
	ssbo_model.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<ModelData*>(data) };
		ptr->model[index] = glm::translate(scale, scaled_position);
	});
	
	model_move_attribs[index].speed = abs(move_direction_dis(gen)) * 10.0f;
	model_move_attribs[index].direction = glm::vec3(
		move_direction_dis(gen), move_direction_dis(gen), move_direction_dis(gen));
}

void quick3d::test::LightBallRenderer::update_instance_position() noexcept
{
	ssbo_model.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<ModelData*>(data) };
		for (int i = 0; i < instance_count; i++)
		{
			const float& speed{ model_move_attribs[i].speed };
			const glm::vec3& direction{ model_move_attribs[i].direction };
			ptr->model[i] = glm::translate(ptr->model[i], speed * direction);
		}
	});

	ssbo_position.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<PositionData*>(data) };
		for (int i = 0; i < instance_count; i++)
		{
			const float& speed{ model_move_attribs[i].speed };
			const glm::vec3& direction{ model_move_attribs[i].direction };
			ptr->position[i] = glm::translate(glm::mat4(1.0f), speed * direction) * ptr->position[i];
			//ptr->position[i] = glm::vec4(100.0f, 0.0f, 0.0f, 0.0f);
		}
	});
}

void quick3d::test::LightBallRenderer::load_shader_program() noexcept(false)
{
	program = new gl::Program(
		gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_ball_vs.glsl")),
		gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_ball_fs.glsl"))
	);

	program->bind_uniform_block("GFXGlobalUBO", 0);

	// 也许不应该放在这里
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, ssbo_model.get_buffer_id());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, ssbo_color.get_buffer_id());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 7, ssbo_position.get_buffer_id());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 8, ssbo_instance_count.get_buffer_id());
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 9, ssbo_attenuation.get_buffer_id());
	ssbo_attenuation.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<AttenuationData*>(data) };
		ptr->constant = 1.0f;
		ptr->linear = 0.09f;
		ptr->quadratic = 0.032f;
	});
}

void quick3d::test::LightBallRenderer::load_model() noexcept(false)
{
	model = new gl::Model(std::format("{}/{}", MODEL_FOLDER, "ball/ball.obj"));
}

quick3d::test::LightBallRenderer::LightBallRenderer() noexcept(false)
	: gen(rd()), position_dis(-10.0, 10.0), move_direction_dis(-1.0, 1.0),
	ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_DYNAMIC_DRAW, sizeof(ModelData)),
	ssbo_color(GL_SHADER_STORAGE_BUFFER, GL_DYNAMIC_DRAW, sizeof(ColorData)),
	ssbo_position(GL_SHADER_STORAGE_BUFFER, GL_DYNAMIC_DRAW, sizeof(PositionData)),
	ssbo_instance_count(GL_SHADER_STORAGE_BUFFER, GL_DYNAMIC_DRAW, sizeof(InstanceCountData)),
	ssbo_attenuation(GL_SHADER_STORAGE_BUFFER, GL_STATIC_DRAW, sizeof(AttenuationData))
		
{
	for (int i = 0; i < 2; i++)
	{
		setup_model_data(0);
		setup_color_data(0);
	}

	load_shader_program();
	load_model();
}

quick3d::test::LightBallRenderer::~LightBallRenderer() noexcept
{
	delete program;
	delete model;
}

void quick3d::test::LightBallRenderer::set_instance_count(int instance) noexcept
{
	for (std::size_t i = instance_count; i < instance; i++)
	{
		setup_model_data(i);
		setup_color_data(i);
	}
	instance_count = instance;

	ssbo_instance_count.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<InstanceCountData*>(data) };
		ptr->light_ball_instance = instance;
	});
}

void quick3d::test::LightBallRenderer::on_tick(float delta_ms) noexcept(false)
{
	update_instance_position();
	draw_model();
}

void quick3d::test::LightBallEntity::try_load_renderer() noexcept(false)
{
	if (!ren)
		ren = std::make_shared<LightBallRenderer>();
}

quick3d::test::LightBallEntity::LightBallEntity(core::EntityManager& manager) noexcept(false)
	: Entity(manager)
{
	try_load_renderer();
}

void quick3d::test::LightBallEntity::set_instance_count(int instance) noexcept
{
	ren->set_instance_count(instance);
}

void quick3d::test::LightBallEntity::on_tick(float delta_ms) noexcept(false)
{
	ren->on_tick(delta_ms);
}
