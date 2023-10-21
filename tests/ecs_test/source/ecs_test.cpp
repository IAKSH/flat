#include <quick_core/sys_gfx.hpp>
#include <quick_core/sys_sfx.hpp>
#include <quick_core/timer.hpp>
#include <quick_core/com_renderer.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/cubemap.hpp>
#include <format>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../tests/outer_glsl/model";
static constexpr std::string_view IMAGE_FOLDER = "../../../../tests/outer_glsl/image";

constexpr std::array<float, 108> skybox_vertices{
	// right
	-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		// left
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		// top
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		// bottom
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		// front
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		// back
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
};

void set_ogl_state() noexcept
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
}

void reset_ogl_state() noexcept
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
}

static std::vector<std::unique_ptr<quick3d::gl::Program>> programs;
static std::vector<std::unique_ptr<quick3d::gl::Model>> models;
static std::vector<std::unique_ptr<quick3d::gl::VertexArray>> vaos;
static std::vector<std::unique_ptr<quick3d::gl::Buffer>> buffers;
static std::vector<std::unique_ptr<quick3d::gl::Texture>> textures;
static std::vector<std::unique_ptr<quick3d::gl::CubeMap>> cubemaps;

static std::vector<quick3d::core::Component*> components;
static std::vector<quick3d::core::Entity*> entities;

quick3d::core::GFXSystem gfx(800, 600);
quick3d::core::SFXSystem sfx;

class YaeEntity : public quick3d::core::Entity
{
public:
	YaeEntity() = default;
	YaeEntity(YaeEntity&) = delete;
	~YaeEntity() = default;
};

class SkyboxEntity : public quick3d::core::Entity
{
public:
	SkyboxEntity() = default;
	SkyboxEntity(SkyboxEntity&) = delete;
	~SkyboxEntity() = default;
};

void setup_model_entity() noexcept
{
	auto program{ std::make_unique<quick3d::gl::Program>(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl")).get_glsl()
	) };
	auto model{ std::make_unique<quick3d::gl::Model>("D:/Programming-Playground/quick3d/tests/outer_glsl/model/yae/yae.obj") };
	auto renderer{ new quick3d::core::ModelRenderer() };
	renderer->bind_camera(&gfx.get_camera());
	renderer->bind_program(program.get());
	renderer->bind_model(model.get());

	auto entity{ new YaeEntity() };
	entity->bind_component(renderer);
	entities.push_back(entity);

	programs.push_back(std::move(program));
	models.push_back(std::move(model));
	components.push_back(renderer);
}

void setup_skybox_entity() noexcept
{
	auto program{ std::make_unique<quick3d::gl::Program>(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_fs.glsl")).get_glsl()
	) };
	auto vbo{ std::make_unique<quick3d::gl::Buffer>(GL_ARRAY_BUFFER,GL_STATIC_DRAW,skybox_vertices.size() * sizeof(float)) };
	vbo->write_buffer_data(skybox_vertices);
	auto vao{ std::make_unique<quick3d::gl::VertexArray>() };
	vao->add_attrib(*vbo, 0, 3, 3, 0);
	auto renderer{ new quick3d::core::SkyboxVAORenderer() };
	renderer->bind_camera(&gfx.get_camera());
	renderer->bind_program(program.get());
	renderer->bind_vbo(vbo.get());
	renderer->bind_vao(vao.get());

	std::array<std::string, 6> skybox_texture_pathes
	{
		std::format("{}/{}", IMAGE_FOLDER, "right.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "left.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "top.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "bottom.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "front.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "back.jpg")
	};
	auto skybox_cubemap{ std::make_unique<quick3d::gl::CubeMap>(GL_RGBA,2048,2048) };
	for (int i = 0; i < 6; i++)
		skybox_cubemap->generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, quick3d::gl::Image(skybox_texture_pathes[i], false));

	renderer->bind_cubemap(skybox_cubemap.get());

	auto entity{ new SkyboxEntity() };
	entity->bind_component(renderer);
	entities.push_back(entity);

	programs.push_back(std::move(program));
	buffers.push_back(std::move(vbo));
	vaos.push_back(std::move(vao));
	cubemaps.push_back(std::move(skybox_cubemap));
	components.push_back(renderer);
}

int main() noexcept
{
	setup_model_entity();
	setup_skybox_entity();

	gfx.capture_mouse();
	quick3d::ecs::HightResTimer timer;
	while (gfx.is_running() && sfx.is_running())
	{
		auto delta{ timer.get_timer_duration<std::chrono::microseconds>().count() / 1000.0f};
		timer.record_time_point();

		set_ogl_state();
		for (auto& entity : entities)
			entity->on_tick(delta);
		reset_ogl_state();

		gfx.on_tick(delta);
		sfx.on_tick(delta);
	}
}