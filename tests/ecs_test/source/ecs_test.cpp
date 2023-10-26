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
#include <ecs_test/box.hpp>
#include <ecs_test/floor.hpp>
#include <ecs_test/light_ball.hpp>

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

int main() noexcept
{
	try
	{
		quick3d::core::GFXSystem gfx(1280, 720);
		quick3d::core::SFXSystem sfx;
		quick3d::core::EntityManager entity_manager;

		entity_manager.add_entity<quick3d::test::SkyboxEntity>("skybox");
		entity_manager.add_entity<quick3d::test::LightBallEntity>("light_ball");
		entity_manager.add_entity<quick3d::test::YaeEntity>("yae");
		entity_manager.add_entity<quick3d::test::BoxEntity>("box");
		entity_manager.add_entity<quick3d::test::FloorEntity>("floor");
			
		ImGui::CreateContext();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init("#version 320 es");

		int yae_instance{ 1 };
		int box_instance{ 1 };
		int light_ball_instance{ 1 };
		float gfx_gamma{ 2.2f };
		glm::vec3 sun_light_ambient(1.0f, 1.0f, 1.0f);
		glm::vec3 sun_light_direction(0.0f, 0.0f, 0.0f);
		quick3d::ecs::HightResTimer timer;
		while (gfx.is_running() && sfx.is_running())
		{
			auto delta{ timer.get_timer_duration<std::chrono::microseconds>().count() / 1000.0f };
			timer.record_time_point();

			gfx.on_tick(delta);
			sfx.on_tick(delta);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// temp code
			gfx.set_gamma(gfx_gamma);
			reinterpret_cast<quick3d::test::LightBallEntity*>(entity_manager.get_entity("light_ball"))->set_instance_count(light_ball_instance);
			reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->set_instance_count(yae_instance);
			reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->set_instance_count(box_instance);
			reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_ambient(sun_light_ambient);
			reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_direction(sun_light_direction);

			set_ogl_state();
			entity_manager.foreach_on_tick(delta);
			reset_ogl_state();

			ImGui::Begin("Control");
			ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::SliderFloat("gamma", &gfx_gamma, 0.0f, 10.0f);
			ImGui::SliderInt("light ball instance", &light_ball_instance, 0, 500);
			ImGui::SliderInt("box instance", &box_instance, 0, 500);
			ImGui::SliderInt("yae instance", &yae_instance, 0, 10);
			ImGui::ColorPicker3("ambient", glm::value_ptr(sun_light_ambient));
			ImGui::SliderFloat3("sun_light_direction", glm::value_ptr(sun_light_direction), -100.0f, 100.0f);
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