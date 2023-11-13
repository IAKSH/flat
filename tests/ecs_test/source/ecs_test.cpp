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
static constexpr std::string_view POINT_SHADOW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_vs.glsl";
static constexpr std::string_view POINT_SHADOW_GLSL_GS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_gs.glsl";
static constexpr std::string_view POINT_SHADOW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_fs.glsl";

static constexpr std::string_view DIRECT_SHADOW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/direct_shadow_vs.glsl";
static constexpr std::string_view DIRECT_SHADOW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/direct_shadow_fs.glsl";

static constexpr std::string_view POST_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/post_vs.glsl";
static constexpr std::string_view POST_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/post_fs.glsl";

static constexpr std::string_view BLUR_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/blur_vs.glsl";
static constexpr std::string_view BLUR_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/blur_fs.glsl";

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

static struct
{
	int yae_instance{ 1 };
	int box_instance{ 1 };
	int light_ball_instance{ 1 };
	bool enable_bilnn_phong{ true };
	bool enable_exposure{ true };
	bool enable_bloom{ true };
	bool enable_point_shadow{ false };
	bool enable_direct_shadow{ true };
	float gamma{ 2.2f };
	float hdr_exposure{ 1.0f };
	glm::vec3 sun_light_ambient{ 1.0f, 1.0f, 1.0f };
	glm::vec3 sun_light_direction{ -10.0f, -10.0f, -10.0f };
}
global_gfx_settings;

struct DirectShadowPass
{
	quick3d::gl::Texture tex;
	quick3d::gl::DepthFramebuffer frame;
	quick3d::gl::Program program;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;
	glm::vec3 light_pos;
	float near_plane;
	float far_plane;

	DirectShadowPass() noexcept(false)
		: tex(GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, true),
		frame(tex),
		program(
			(quick3d::gl::GLSLReader(DIRECT_SHADOW_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(DIRECT_SHADOW_GLSL_FS_PATH))
		),
		near_plane(1.0f),
		far_plane(25.0f)
	{
	}

	void draw(quick3d::core::GFXSystem& gfx, quick3d::core::EntityManager& entity_manager, float delta) noexcept(false)
	{
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
		glClear(GL_DEPTH_BUFFER_BIT);

		light_pos = -global_gfx_settings.sun_light_direction;
		// 这个投影有问题
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightSpaceMatrix = lightProjection * lightView;
		gfx.set_lightspace_matrix(lightSpaceMatrix);
		program.set_uniform("lightSpaceMatrix", lightSpaceMatrix);
		entity_manager.foreach([&](std::string name, quick3d::core::Entity* entity)
		{
			if (name != "light_ball" && name != "skybox")
				entity->on_darw_with_shader(delta, program);
		});
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
};

struct PointShadowPass
{
	quick3d::gl::DepthCubeMap cubemap;
	quick3d::gl::DepthFramebuffer frame;
	quick3d::gl::Program program;
	float near_plane;
	float far_plane;
	glm::vec3 light_pos;
	glm::mat4 shadow_proj;
	std::array<glm::mat4,6> shadow_transforms;
	
	PointShadowPass() noexcept(false)
		: cubemap(SHADOW_WIDTH, SHADOW_HEIGHT),
		frame(cubemap),
		program(
			(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_GS_PATH)),
			(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_FS_PATH))
		),
		shadow_proj(glm::perspective(glm::radians(90.0f), SHADOW_WIDTH / SHADOW_HEIGHT, near_plane, far_plane)),
		near_plane(1.0f),
		far_plane(25.0f)
	{
	}

	void draw(quick3d::core::GFXSystem& gfx,quick3d::core::EntityManager& entity_manager,float delta) noexcept(false)
	{
		light_pos = -global_gfx_settings.sun_light_direction;
		shadow_transforms[0] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		shadow_transforms[1] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		shadow_transforms[2] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shadow_transforms[3] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		shadow_transforms[4] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		shadow_transforms[5] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		for (unsigned int i = 0; i < 6; ++i)
			program.set_uniform(std::format("shadowMatrices[{}]", i), shadow_transforms[i]);
		program.set_uniform("far_plane", far_plane);
		program.set_uniform("lightPos", light_pos);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
		glClear(GL_DEPTH_BUFFER_BIT);
		entity_manager.foreach([&](std::string name, quick3d::core::Entity* entity)
		{
			if (name != "light_ball" && name != "skybox")
				entity->on_darw_with_shader(delta, program);
		});
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
};

struct RawScenePass
{


	void draw() noexcept(false)
	{
		
	}
};

struct BloomPass
{
	void draw() noexcept(false)
	{
		
	}
};

struct HDRBlendPass
{
	quick3d::gl::Buffer vbo;
	quick3d::gl::VertexArray vao;
	quick3d::gl::Program hdr_blend_program;
	quick3d::gl::Program blur_program;
	quick3d::gl::Texture scene_tex;
	quick3d::gl::Texture blur_tex;
	std::array<quick3d::gl::Texture, 2> blur_pingpong_texs;
	std::array<quick3d::gl::ColorFramebuffer, 2> blur_pingpong_frames;
	quick3d::gl::ColorFramebuffer hdr_bloom_frame;

	HDRBlendPass() noexcept(false)
		: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
		hdr_blend_program(
			(quick3d::gl::GLSLReader(POST_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(POST_GLSL_FS_PATH))
		),
		blur_program(
			(quick3d::gl::GLSLReader(BLUR_GLSL_VS_PATH)),
			(quick3d::gl::GLSLReader(BLUR_GLSL_FS_PATH))
		),
		scene_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
		blur_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
		blur_pingpong_texs{
			quick3d::gl::Texture(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
			quick3d::gl::Texture(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true)
		},
		blur_pingpong_frames{
			quick3d::gl::ColorFramebuffer(SCREEN_WIDTH, SCREEN_HEIGHT),
			quick3d::gl::ColorFramebuffer(SCREEN_WIDTH, SCREEN_HEIGHT)
		},
		hdr_bloom_frame(SCREEN_WIDTH, SCREEN_HEIGHT)
	{
		vbo.write_buffer_data(QUAD_VERTICES);
		vao.add_attrib(vbo, 0, 3, 5, 0);
		vao.add_attrib(vbo, 1, 2, 5, 3);

		hdr_bloom_frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT0, scene_tex.get_tex_id());
		hdr_bloom_frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT1, blur_tex.get_tex_id());

		for (int i = 0; i < 2; i++)
			blur_pingpong_frames[i].bind_texture_to_fbo(GL_COLOR_ATTACHMENT0, blur_pingpong_texs[i].get_tex_id());

		hdr_bloom_frame.set_draw_targets({ GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 });
		hdr_blend_program.set_uniform("sceneTex", 0);
		hdr_blend_program.set_uniform("bloomTex", 1);
		blur_program.set_uniform("horizontal", 1);
	}

	void draw(quick3d::core::EntityManager& entity_manager, float delta, DirectShadowPass& direct_shadow_pass, PointShadowPass& point_shadow_pass) noexcept(false)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, hdr_bloom_frame.get_fbo_id());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, direct_shadow_pass.tex.get_tex_id());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, point_shadow_pass.cubemap.get_cubemap_id());

		entity_manager.foreach_on_draw(delta);

		// 两步高斯模糊（乒乓式）
		bool horizontal{ true };
		bool first_iteration{ true };
		unsigned int amount = 10;
		for (int i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, blur_pingpong_frames[i].get_fbo_id());
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		for (unsigned int i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, blur_pingpong_frames[horizontal].get_fbo_id());
			blur_program.set_uniform("horizontal", static_cast<int>(horizontal));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(
				GL_TEXTURE_2D, (first_iteration ? blur_tex : blur_pingpong_texs[!horizontal]).get_tex_id()
			);
			vao.draw(blur_program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
			horizontal = !horizontal;
			if (first_iteration)
				first_iteration = false;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 混合所有后期处理并输出到屏幕
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene_tex.get_tex_id());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, blur_pingpong_texs[!horizontal].get_tex_id());
		hdr_blend_program.set_uniform("exposure", global_gfx_settings.hdr_exposure);
		hdr_blend_program.set_uniform("enable_exposure", static_cast<int>(global_gfx_settings.enable_exposure));
		hdr_blend_program.set_uniform("enableBloom", static_cast<int>(global_gfx_settings.enable_bloom));
		vao.draw(hdr_blend_program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

void draw_imgui(quick3d::core::GFXSystem& gfx, ImGuiIO& io) noexcept
{
	ImGui::Begin("Control");
	ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	float cam_pos_x{ gfx.get_camera().get_position().x };
	float cam_pos_y{ gfx.get_camera().get_position().y };
	float cam_pos_z{ gfx.get_camera().get_position().z };
	ImGui::Text(" camera pos: (%.1f,%.1f,%.1f) ", cam_pos_x, cam_pos_y, cam_pos_z);
	ImGui::Checkbox("Bilnn-Phong lighting", &global_gfx_settings.enable_bilnn_phong);
	ImGui::SliderFloat("gamma", &global_gfx_settings.gamma, 0.0f, 10.0f);
	ImGui::SliderInt("light ball instance", &global_gfx_settings.light_ball_instance, 0, 500);
	ImGui::SliderInt("box instance", &global_gfx_settings.box_instance, 0, 500);
	ImGui::SliderInt("yae instance", &global_gfx_settings.yae_instance, 0, 10);
	ImGui::ColorPicker3("ambient", glm::value_ptr(global_gfx_settings.sun_light_ambient));
	ImGui::SliderFloat3("sun_light_direction", glm::value_ptr(global_gfx_settings.sun_light_direction), -10.0f, 10.0f);
	ImGui::SliderFloat("hdr_exposure", &global_gfx_settings.hdr_exposure, 0.0f, 10.0f);
	ImGui::Checkbox("enable_exposure", &global_gfx_settings.enable_exposure);
	ImGui::Checkbox("enable_bloom", &global_gfx_settings.enable_bloom);
	ImGui::Checkbox("(force) enable_point_shadow", &global_gfx_settings.enable_point_shadow);
	ImGui::Checkbox("enable_direct_shadow", &global_gfx_settings.enable_direct_shadow);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void on_tick(quick3d::core::GFXSystem& gfx, quick3d::core::EntityManager& entity_manager, float delta) noexcept
{
	global_gfx_settings.sun_light_direction.x = sin(glfwGetTime() / 50.0f) * 10.0f;
	global_gfx_settings.sun_light_direction.z = cos(glfwGetTime() / 50.0f) * 10.0f;

	gfx.switch_direct_shadow(global_gfx_settings.enable_direct_shadow);
	gfx.switch_point_shadow(global_gfx_settings.enable_point_shadow);
	gfx.set_gamma(global_gfx_settings.gamma);

	reinterpret_cast<quick3d::test::LightBallEntity*>(entity_manager.get_entity("light_ball"))->set_instance_count(global_gfx_settings.light_ball_instance);
	reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->set_instance_count(global_gfx_settings.yae_instance);
	reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->set_instance_count(global_gfx_settings.box_instance);
	reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_ambient(global_gfx_settings.sun_light_ambient);
	reinterpret_cast<quick3d::test::SkyboxEntity*>(entity_manager.get_entity("skybox"))->set_light_direction(global_gfx_settings.sun_light_direction);
	reinterpret_cast<quick3d::test::YaeEntity*>(entity_manager.get_entity("yae"))->switch_blinn_phong_lighting(global_gfx_settings.enable_bilnn_phong);
	reinterpret_cast<quick3d::test::BoxEntity*>(entity_manager.get_entity("box"))->switch_blinn_phong_lighting(global_gfx_settings.enable_bilnn_phong);
	reinterpret_cast<quick3d::test::FloorEntity*>(entity_manager.get_entity("floor"))->switch_blinn_phong_lighting(global_gfx_settings.enable_bilnn_phong);

	entity_manager.foreach_on_tick(delta);	
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

		DirectShadowPass direct_shadow_pass;
		PointShadowPass point_shadow_pass;
		//RawScenePass raw_scene_pass;
		HDRBlendPass hdr_blend_pass;
		
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
			
			// 逐Pass绘制
			direct_shadow_pass.draw(gfx, entity_manager, delta);
			point_shadow_pass.draw(gfx, entity_manager, delta);
			//raw_scene_pass.draw();
			hdr_blend_pass.draw(entity_manager, delta, direct_shadow_pass, point_shadow_pass);

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