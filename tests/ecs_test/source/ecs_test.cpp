#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <quick_core/sys_gfx.hpp>
#include <quick_core/sys_sfx.hpp>
#include <quick_core/timer.hpp>
#include <quick_core/com_renderer.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/frame.hpp>
#include <format>

#include <ecs_test/yae.hpp>
#include <ecs_test/skybox.hpp>
#include <ecs_test/box.hpp>
#include <ecs_test/floor.hpp>
#include <ecs_test/light_ball.hpp>
#include <ecs_test/my_passes.hpp>

#define IMGUI_IMPL_OPENGL_ES3

quick3d::test::DemoSettings settings;

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

void draw_imgui(quick3d::core::GFXSystem& gfx, ImGuiIO& io) noexcept
{
	ImGui::Begin("Control");
	ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	float cam_pos_x{ gfx.get_camera().get_position().x };
	float cam_pos_y{ gfx.get_camera().get_position().y };
	float cam_pos_z{ gfx.get_camera().get_position().z };
	ImGui::Text(" camera pos: (%.1f,%.1f,%.1f) ", cam_pos_x, cam_pos_y, cam_pos_z);
	ImGui::Checkbox("Bilnn-Phong lighting", &settings.enable_bilnn_phong);
	ImGui::SliderFloat("gamma", &settings.gamma, 0.0f, 10.0f);
	ImGui::SliderInt("light ball instance", &settings.light_ball_instance, 0, 500);
	ImGui::SliderInt("box instance", &settings.box_instance, 0, 500);
	ImGui::SliderInt("yae instance", &settings.yae_instance, 0, 10);
	ImGui::ColorPicker3("ambient", glm::value_ptr(settings.sun_light_ambient));
	ImGui::SliderFloat3("sun_light_direction", glm::value_ptr(settings.sun_light_direction), -10.0f, 10.0f);
	ImGui::SliderFloat("hdr_exposure", &settings.hdr_exposure, 0.0f, 10.0f);
	ImGui::Checkbox("enable_exposure", &settings.enable_exposure);
	ImGui::Checkbox("enable_bloom", &settings.enable_bloom);
	ImGui::Checkbox("(force) enable_point_shadow", &settings.enable_point_shadow);
	ImGui::Checkbox("enable_direct_shadow", &settings.enable_direct_shadow);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void on_tick(quick3d::core::GFXSystem& gfx, quick3d::core::EntityManager& entity_manager, float delta) noexcept
{
	settings.sun_light_direction.x = sin(glfwGetTime() / 50.0f) * 10.0f;
	settings.sun_light_direction.z = cos(glfwGetTime() / 50.0f) * 10.0f;

	gfx.switch_direct_shadow(settings.enable_direct_shadow);
	gfx.switch_point_shadow(settings.enable_point_shadow);
	gfx.set_gamma(settings.gamma);

	reinterpret_cast<quick3d::test::LightBallEntity*>(entity_manager.get_entity("light_ball"))->set_instance_count(settings.light_ball_instance);
	reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->set_instance_count(settings.yae_instance);
	reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->set_instance_count(settings.box_instance);
	reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_ambient(settings.sun_light_ambient);
	reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_direction(settings.sun_light_direction);
	reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->switch_blinn_phong_lighting(settings.enable_bilnn_phong);
	reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->switch_blinn_phong_lighting(settings.enable_bilnn_phong);
	reinterpret_cast<quick3d::test::FloorEntity*>(entity_manager.get_entity("floor"))->switch_blinn_phong_lighting(settings.enable_bilnn_phong);

	entity_manager.foreach_on_tick(delta);	
}

int main() noexcept
{
	try
	{
		quick3d::core::GFXSystem gfx(quick3d::test::SCREEN_WIDTH, quick3d::test::SCREEN_HEIGHT);
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
		ImGui_ImplOpenGL3_Init("#version 330 core");

		quick3d::test::Pipeline pipeline;
		pipeline.add_pass<quick3d::test::DirectShadowPass>("direct_shadow_pass", gfx, entity_manager, settings);
		pipeline.add_pass<quick3d::test::PointShadowPass>("point_shadow_pass", entity_manager, settings);
		pipeline.add_pass<quick3d::test::RawScenePass>("raw_scene_pass", entity_manager);
		pipeline.add_pass<quick3d::test::BloomPass>("bloom_pass");
		pipeline.add_pass<quick3d::test::HDRBlendPass>("hdr_blend_pass", settings);
		
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

			on_tick(gfx, entity_manager, delta);
			set_ogl_state();
			pipeline.exec(delta);
			reset_ogl_state();
			draw_imgui(gfx, io);
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