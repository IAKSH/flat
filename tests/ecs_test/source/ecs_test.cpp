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

#include <ecs_test/yae.hpp>
#include <ecs_test/skybox.hpp>

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

// temp code
// TODO: 可能需要并入gfx.on_tick()
void update_camera_ubo(quick3d::core::GFXSystem& gfx, quick3d::gl::Buffer& ubo, auto& data) noexcept
{
	data.projection = gfx.get_camera().get_projection_matrix();
	data.view = gfx.get_camera().get_view_matrix();
	ubo.write_buffer_data(&data, 0, sizeof(data));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.get_buffer_id());
}

int main() noexcept
{
	try
	{
		quick3d::core::GFXSystem gfx(800, 600);
		quick3d::core::SFXSystem sfx;
		quick3d::core::EntityManager entity_manager;

		// temp code
		// TODO: 可能需要并入gfx.on_tick()
		struct
		{
			glm::mat4 projection;
			glm::mat4 view;
		} camera_ubo_data;
		auto camera_ubo{ std::make_unique<quick3d::gl::Buffer>(GL_UNIFORM_BUFFER,GL_STREAM_DRAW,sizeof(camera_ubo_data)) };

		entity_manager.add_entity<quick3d::test::SkyboxEntity>("skybox");
		entity_manager.add_entity<quick3d::test::YaeEntity>("yae");

		// TODO：应当也在UBO中实现，在UBO中加入没有位移信息的view矩阵
		reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->bind_camera(gfx.get_camera());
			
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
			update_camera_ubo(gfx, *camera_ubo, camera_ubo_data);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// temp code
			reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->set_instance_count(instance_count);

			set_ogl_state();
			entity_manager.foreach_on_tick(delta);
			reset_ogl_state();

			ImGui::Begin("Control");
			ImGui::SliderInt("instance count", &instance_count, 0, 10);
			ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();

			ImGui::Render();
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