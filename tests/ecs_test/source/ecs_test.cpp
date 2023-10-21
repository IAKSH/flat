#include <quick_ecs/sys_gfx.hpp>
#include <quick_ecs/sys_sfx.hpp>
#include <quick_ecs/timer.hpp>
#include <quick_ecs/com_renderer.hpp>

#include <quick_gl/model.hpp>
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

void load_cubemap(quick3d::ecs::CubemapRenderer& ren) noexcept
{
	ren.add_vao_target(skybox_vertices);
	//ren.add_vao_target(skybox_vertices.data(), skybox_vertices.size() * sizeof(float));
	std::array<std::string, 6> skybox_texture_pathes
	{
		std::format("{}/{}", IMAGE_FOLDER, "right.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "left.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "top.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "bottom.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "front.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "back.jpg")
	};

	for (int i = 0; i < 6; i++)
		ren.add_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, skybox_texture_pathes[i]);
}

int main() noexcept
{
	quick3d::ecs::GfxSystem gfx(800, 600);
	quick3d::ecs::SfxSystem sfx;
	gfx.on_attach();
	sfx.on_attach();
	gfx.capture_mouse();

	quick3d::ecs::Renderer model_ren(
		gfx.get_camera(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl")).get_glsl()
	);
	model_ren.on_attach();
	model_ren.add_model_target("D:/Programming-Playground/quick3d/tests/outer_glsl/model/yae/yae.obj");

	quick3d::ecs::SkyboxRenderer skybox_ren(
		gfx.get_camera(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_fs.glsl")).get_glsl(),
		GL_RGBA, 2048, 2048
	);
	skybox_ren.on_attach();
	load_cubemap(skybox_ren);

	quick3d::ecs::HightResTimer timer;
	while (gfx.is_running() && sfx.is_running())
	{
		auto delta{ timer.get_timer_duration<std::chrono::microseconds>().count() / 1000.0f};
		timer.record_time_point();

		gfx.on_tick(delta);
		sfx.on_tick(delta);

		skybox_ren.on_tick(delta);
		set_ogl_state();
		model_ren.on_tick(delta);
		reset_ogl_state();
	}

	//ren.on_disattach();
	gfx.on_disattach();
	sfx.on_disattach();
}