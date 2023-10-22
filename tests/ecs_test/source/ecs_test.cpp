#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <quick_core/sys_gfx.hpp>
#include <quick_core/sys_sfx.hpp>
#include <quick_core/timer.hpp>
#include <quick_core/com_renderer.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/cubemap.hpp>
#include <format>

#include <ecs_test/entity_yae.hpp>
#include <ecs_test/entity_skybox.hpp>

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

static std::vector<std::unique_ptr<quick3d::gl::Program>> programs;
static std::vector<std::unique_ptr<quick3d::gl::Model>> models;
static std::vector<std::unique_ptr<quick3d::gl::VertexArray>> vaos;
static std::vector<std::unique_ptr<quick3d::gl::Buffer>> buffers;
static std::vector<std::unique_ptr<quick3d::gl::Texture>> textures;
static std::vector<std::unique_ptr<quick3d::gl::CubeMap>> cubemaps;
static std::vector<quick3d::core::Component*> components;
static std::vector<quick3d::core::Entity*> entities;
static quick3d::core::GFXSystem gfx(800, 600);
static quick3d::core::SFXSystem sfx;

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

// temp
quick3d::core::InstanceModelRenderer* instance_renderer;

void setup_model_entity() noexcept
{
	auto program{ std::make_unique<quick3d::gl::Program>(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl")).get_glsl()
	) };
	program->bind_uniform_block("CameraMatrix", 0);
	auto model{ std::make_unique<quick3d::gl::Model>("D:/Programming-Playground/quick3d/tests/outer_glsl/model/yae/yae.obj") };
	auto renderer{ new quick3d::core::InstanceModelRenderer() };
	renderer->set_instance_count(10);
	renderer->bind_program(program.get());
	renderer->bind_model(model.get());

	auto entity{ new quick3d::test::YaeEntity() };
	entity->bind_component(renderer);
	entities.push_back(entity);

	programs.push_back(std::move(program));
	models.push_back(std::move(model));
	components.push_back(renderer);

	// temp
	instance_renderer = renderer;
}

void setup_skybox_entity() noexcept
{
	auto program{ std::make_unique<quick3d::gl::Program>(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_fs.glsl")).get_glsl()
	) };
	program->bind_uniform_block("CameraMatrix", 0);
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

	auto entity{ new quick3d::test::SkyboxEntity() };
	entity->bind_component(renderer);
	entities.push_back(entity);

	programs.push_back(std::move(program));
	buffers.push_back(std::move(vbo));
	vaos.push_back(std::move(vao));
	cubemaps.push_back(std::move(skybox_cubemap));
	components.push_back(renderer);
}

static struct Data
{
	glm::mat4 projection;
	glm::mat4 view;
} data;
static auto camera_ubo{ std::make_unique<quick3d::gl::Buffer>(GL_UNIFORM_BUFFER,GL_STREAM_DRAW,sizeof(data)) };

void update_camera_ubo() noexcept
{
	data.projection = gfx.get_camera().get_projection_matrix();
	data.view = gfx.get_camera().get_view_matrix();
	camera_ubo->write_buffer_data(&data, 0, sizeof(data));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, camera_ubo->get_buffer_id());
}

int main() noexcept
{
	try
	{
		setup_model_entity();
		setup_skybox_entity();

		ImGui::CreateContext();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init("#version 320 es");

		//gfx.capture_mouse();
		int instance_count{ 1 };
		quick3d::ecs::HightResTimer timer;
		while (gfx.is_running() && sfx.is_running())
		{
			auto delta{ timer.get_timer_duration<std::chrono::microseconds>().count() / 1000.0f };
			timer.record_time_point();

			gfx.on_tick(delta);
			sfx.on_tick(delta);
			update_camera_ubo();

			instance_renderer->set_instance_count(instance_count);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			set_ogl_state();
			for (auto& entity : entities)
				entity->on_tick(delta);
			reset_ogl_state();

			ImGui::Begin("Control");
			ImGui::SliderInt("instance count", &instance_count, 0, 10);
			ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();

			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(glfwGetCurrentContext(), &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}