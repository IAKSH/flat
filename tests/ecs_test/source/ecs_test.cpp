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

#define IMGUI_IMPL_OPENGL_ES3

// TODO: 还是不行，需要给Model，VAO之类的东西按着之前Renderer的多态结构再分别写一套阴影着色器。
//       不对，Model最后不也是VAO吗... 如果能统一model矩阵之类的接口，就能实现阴影着色器的复用了。
//       其实现在的问题也就是model矩阵之类的接口不统一吧... 现在的SSBO model似乎是各自用不同的绑定点，如果是共用统一的绑定点，然后绘制之前把自己的SSBO model绑上去呢？
//       然后SSBO在GLSL中的接口还是可变长度的，非常的合理。
static constexpr std::string_view MODEL_SHADOW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/model_shadow_vs.glsl";
static constexpr std::string_view MODEL_SHADOW_GLSL_GS_PATH = "../../../../tests/ecs_test/glsl/model_shadow_gs.glsl";
static constexpr std::string_view MODEL_SHADOW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/model_shadow_fs.glsl";

static constexpr std::string_view HDR_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/hdr_vs.glsl";
static constexpr std::string_view HDR_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/hdr_fs.glsl";

static constexpr int SCREEN_WIDTH{ 1280 };
static constexpr int SCREEN_HEIGHT{ 720 };
static constexpr float SHADOW_WIDTH{ 2048 };
static constexpr float SHADOW_HEIGHT{ 2048 };

static constexpr std::array<float,20> QUAD_VERTICES
{
	// Positions        // Texture Coords
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
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

int main() noexcept
{
	try
	{
		quick3d::core::GFXSystem gfx(SCREEN_WIDTH, SCREEN_HEIGHT);
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

		// shadow test begin
		quick3d::gl::DepthCubeMap depth_cubemap(SHADOW_WIDTH, SHADOW_HEIGHT);
		quick3d::gl::DepthFramebuffer depth_framebuffer(depth_cubemap);
		quick3d::gl::Program shadow_program(
			(quick3d::gl::GLSLReader(MODEL_SHADOW_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(MODEL_SHADOW_GLSL_GS_PATH)),
			(quick3d::gl::GLSLReader(MODEL_SHADOW_GLSL_FS_PATH)));
		// shadow test end

		// HDR test begin
		quick3d::gl::Buffer hdr_frame_vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES));
		hdr_frame_vbo.write_buffer_data(QUAD_VERTICES);
		quick3d::gl::VertexArray hdr_frame_vao;
		hdr_frame_vao.add_attrib(hdr_frame_vbo, 0, 3, 5, 0);
		hdr_frame_vao.add_attrib(hdr_frame_vbo, 1, 2, 5, 3);
		quick3d::gl::Program hdr_frame_program(
			(quick3d::gl::GLSLReader(HDR_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(HDR_GLSL_FS_PATH))
		);
 		quick3d::gl::Texture hdr_frame_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true);
		quick3d::gl::ColorFramebuffer hdr_framebuffer(hdr_frame_tex);
		// HDR test end

		int yae_instance{ 1 };
		int box_instance{ 1 };
		int light_ball_instance{ 1 };
		bool enable_bilnn_phong{ true };
		bool enable_exposure{ true };
		float gfx_gamma{ 2.2f };
		float hdr_exposure{ 1.0f };
		glm::vec3 sun_light_ambient(1.0f, 1.0f, 1.0f);
		glm::vec3 sun_light_direction(-10.0f, -10.0f, -10.0f);
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

			reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->switch_blinn_phong_lighting(enable_bilnn_phong);
			reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->switch_blinn_phong_lighting(enable_bilnn_phong);
			reinterpret_cast<quick3d::test::FloorEntity*>(entity_manager.get_entity("floor"))->switch_blinn_phong_lighting(enable_bilnn_phong);

			entity_manager.foreach_on_tick(delta);

			set_ogl_state();
			// shadow test begin
			float near_plane = 0.01f;
			float far_plane = 25.0f;
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
			std::vector<glm::mat4> shadowTransforms;

			sun_light_direction.x = sin(glfwGetTime() / 50.0f) * 10.0f;
			sun_light_direction.z = cos(glfwGetTime() / 50.0f) * 10.0f;

			glm::vec3 lightPos{ -sun_light_direction };
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			for (unsigned int i = 0; i < 6; ++i)
				shadow_program.set_uniform(std::format("shadowMatrices[{}]", i), shadowTransforms[i]);
			shadow_program.set_uniform("far_plane", far_plane);
			shadow_program.set_uniform("lightPos", lightPos);

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depth_framebuffer.get_fbo_id());
			glClear(GL_DEPTH_BUFFER_BIT);
			//entity_manager.foreach_on_draw(delta, shadow_program);
			entity_manager.foreach([&](std::string name, quick3d::core::Entity* entity)
			{
				if (name != "light_ball" && name != "skybox")
					entity->on_darw_with_shader(delta, shadow_program);
			});
			glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			// hdr test start
			glBindFramebuffer(GL_FRAMEBUFFER, hdr_framebuffer.get_fbo_id());
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_CUBE_MAP, depth_cubemap.get_cubemap_id());
			// shadow test end
			entity_manager.foreach_on_draw(delta);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, hdr_frame_tex.get_tex_id());
			hdr_frame_program.set_uniform("exposure", hdr_exposure);
			hdr_frame_program.set_uniform("enable_exposure", static_cast<int>(enable_exposure));
			hdr_frame_vao.draw(hdr_frame_program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
			glBindTexture(GL_TEXTURE_2D, 0);
			// hdr test end
			reset_ogl_state();

			ImGui::Begin("Control");
			ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			float cam_pos_x{ gfx.get_camera().get_position().x };
			float cam_pos_y{ gfx.get_camera().get_position().y };
			float cam_pos_z{ gfx.get_camera().get_position().z };
			ImGui::Text(" camera pos: (%.1f,%.1f,%.1f) ", cam_pos_x, cam_pos_y, cam_pos_z);
			ImGui::Checkbox("Bilnn-Phong lighting", &enable_bilnn_phong);
			ImGui::SliderFloat("gamma", &gfx_gamma, 0.0f, 10.0f);
			ImGui::SliderInt("light ball instance", &light_ball_instance, 0, 500);
			ImGui::SliderInt("box instance", &box_instance, 0, 500);
			ImGui::SliderInt("yae instance", &yae_instance, 0, 10);
			ImGui::ColorPicker3("ambient", glm::value_ptr(sun_light_ambient));
			ImGui::SliderFloat3("sun_light_direction", glm::value_ptr(sun_light_direction), -10.0f, 10.0f);
			ImGui::SliderFloat("hdr_exposure", &hdr_exposure, 0.0f, 10.0f);
			ImGui::Checkbox("enable_exposure", &enable_exposure);
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