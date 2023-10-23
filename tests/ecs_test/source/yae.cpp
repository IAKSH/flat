#include <ecs_test/yae.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../tests/outer_glsl/model";

void quick3d::test::YaeRenderer::setup_model_data() noexcept(false)
{
	auto model{ glm::scale(glm::mat4(1.0f),glm::vec3(0.001f,0.001f,0.001f)) };
	for (int i = 0; i < 10; i++)
		model_data.model[i] = glm::translate(model, glm::vec3(i, 0.0f, 0.0f));

	ssbo_model.write_buffer_data(&model_data, 0, sizeof(ModelData));
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
}

void quick3d::test::YaeRenderer::load_shader_program() noexcept(false)
{
	program = new quick3d::gl::Program(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl")).get_glsl()
	);
	program->bind_uniform_block("CameraMatrix", 0);
}

void quick3d::test::YaeRenderer::load_model() noexcept(false)
{
	model = new quick3d::gl::Model("D:/Programming-Playground/quick3d/tests/outer_glsl/model/yae/yae.obj");
}

void quick3d::test::YaeRenderer::modify_renderer() noexcept
{
	instance_count = 10;
}

quick3d::test::YaeRenderer::YaeRenderer() noexcept(false)
	: ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_STATIC_DRAW, sizeof(model_data))
{
	load_shader_program();
	load_model();
	modify_renderer();
	setup_model_data();
}

quick3d::test::YaeRenderer::~YaeRenderer() noexcept
{
	delete program;
	delete model;
}

void quick3d::test::YaeRenderer::set_instance_count(int instance) noexcept
{
	instance_count = instance;
}

quick3d::test::YaeEntity::YaeEntity(core::EntityManager& manager) noexcept
	: Entity(manager)
{
}

void quick3d::test::YaeEntity::set_instance_count(int instance) noexcept
{
	ren.set_instance_count(instance);
}

void quick3d::test::YaeEntity::on_tick(float delta_ms) noexcept(false)
{
	ren.on_tick(delta_ms);
}
