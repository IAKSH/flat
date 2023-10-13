#include <array>
#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/model.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/light_ball/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../../tests/light_ball/model";
static constexpr std::string_view IMAGE_FOLDER = "../../../../../tests/light_ball/image";

static constexpr int SCR_WIDTH = 800;
static constexpr int SCR_HEIGHT = 600;

constexpr std::array<float, 216> cube_vertices_with_normal{
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
};

constexpr std::array<float, 108> cube_vertices{
	-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f
};

constexpr std::array<float, 288> cube_vertices_for_light_maps
{
	// positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

void run() noexcept(false)
{
	quick3d::gl::Context context("light test", SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	quick3d::gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

	quick3d::gl::Program cube_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"cube_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "cube_fs.glsl"))
	);

	quick3d::gl::Program cube_light_maps_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"cube_light_maps_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "cube_light_maps_fs.glsl"))
	);

	quick3d::gl::Program parallel_light_cube_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"cube_light_maps_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "parallel_light_cube_fs.glsl"))
	);

	quick3d::gl::Program light_program(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_fs.glsl"))
	);

	quick3d::gl::Program model_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"model_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_fs.glsl"))
	);

	quick3d::gl::Program model_tex_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"model_tex_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "model_tex_fs.glsl"))
	);

	quick3d::gl::VBO cube_vbo(cube_vertices_with_normal);
	quick3d::gl::VAO cube_vao(cube_vbo);
	cube_vao.enable_attrib(0, 3, 6, 0);
	cube_vao.enable_attrib(1, 3, 6, 3);

	quick3d::gl::VBO cube_with_light_maps_vbo(cube_vertices_for_light_maps);
	quick3d::gl::VAO cube_with_light_maps_vao(cube_with_light_maps_vbo);
	cube_with_light_maps_vao.enable_attrib(0,3,8,0);
	cube_with_light_maps_vao.enable_attrib(1,3,8,3);
	cube_with_light_maps_vao.enable_attrib(2,2,8,6);

	quick3d::gl::VBO light_vbo(cube_vertices);
	quick3d::gl::VAO light_vao(light_vbo);
	light_vao.enable_attrib(0, 3, 3, 0);

	quick3d::gl::Model ball_model(std::format("{}/{}",MODEL_FOLDER,"ball/ball.obj"));
	quick3d::gl::Model yoimiya_model(std::format("{}/{}",MODEL_FOLDER,"yoimiya/yoimiya.obj"));

	quick3d::gl::Texture container_diffuse_tex(GL_RGBA,quick3d::gl::Image(std::format("{}/{}",IMAGE_FOLDER,"container2.png")));
	quick3d::gl::Texture container_specular_tex(GL_RGBA,quick3d::gl::Image(std::format("{}/{}",IMAGE_FOLDER,"container2_specular.png")));

	context.get_window(0).set_mouse_callback([&](GLFWwindow* win, double x, double y) { camera.process_mouse_input(win, x, y); });
	context.get_window(0).set_keybord_callback([&](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			camera.process_keyboard_input(win, 0.01f);

			if (action == GLFW_PRESS)
			{
				switch (key)
				{
				case GLFW_KEY_ESCAPE:
					glfwSetWindowShouldClose(win, true);
					break;

				default:
					break;
				}
			} });

	double delta_time{ 0 };
	double last_frame{ 0 };
	double current_frame{ 0 };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 light_pos;
	glm::vec3 light_diffuse;

	auto win{ context.get_window(0).get_glfw_window() };
	while (!glfwWindowShouldClose(win))
	{
		light_pos =  glm::vec3(sin(glfwGetTime()) * 10.0f,sin(glfwGetTime()) * 10.0f, 0.0f);
		light_diffuse = glm::vec3(abs(sin(glfwGetTime()) / 2.0f), abs(cos(glfwGetTime()) / 2.0f), 0.5f);

		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		camera.on_tick(static_cast<float>(delta_time) * 10);

		// draw
		model_program.set_uniform("view", camera.get_view_matrix());
		model_program.set_uniform("projection", camera.get_projection_matrix());
		model_program.set_uniform("model",
			glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 5.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()), glm::vec3(sin(glfwGetTime()) * 10.0f, cos(glfwGetTime()) * 10.0f, 0.0f))
			);
		model_program.set_uniform("viewPos", camera.get_position());
		model_program.set_uniform("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		model_program.set_uniform("material.diffuse", glm::vec3(0.7f, 0.2f, 0.3f));
		model_program.set_uniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		model_program.set_uniform("material.shininess", 64.0f);
		model_program.set_uniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		model_program.set_uniform("light.diffuse", light_diffuse);
		model_program.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		model_program.set_uniform("light.position", light_pos);
		ball_model.draw_model(model_program);

		model_tex_program.set_uniform("view", camera.get_view_matrix());
		model_tex_program.set_uniform("projection", camera.get_projection_matrix());
		model_tex_program.set_uniform("model",
			glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 5.0f, 0.0f)) 
			);
		model_tex_program.set_uniform("viewPos", camera.get_position());
		model_tex_program.set_uniform("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		model_tex_program.set_uniform("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		model_tex_program.set_uniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		model_tex_program.set_uniform("material.shininess", 0.1f);
		model_tex_program.set_uniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		model_tex_program.set_uniform("light.diffuse", light_diffuse);
		model_tex_program.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		model_tex_program.set_uniform("light.position", light_pos);
		yoimiya_model.draw_model(model_tex_program);

		light_program.set_uniform("view", camera.get_view_matrix());
		light_program.set_uniform("projection", camera.get_projection_matrix());
		light_program.set_uniform("model", glm::translate(glm::mat4(1.0f), light_pos));
		light_program.set_uniform("lightColor", light_diffuse);
		light_vao.draw(light_program, GL_TRIANGLES, 0, 36);

		cube_program.set_uniform("view", camera.get_view_matrix());
		cube_program.set_uniform("projection", camera.get_projection_matrix());
		cube_program.set_uniform("model",
			glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()), glm::vec3(sin(glfwGetTime()) * 10.0f, cos(glfwGetTime()) * 10.0f, 0.0f))
			);
		cube_program.set_uniform("viewPos", camera.get_position());
		cube_program.set_uniform("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		cube_program.set_uniform("material.diffuse", glm::vec3(0.7f, 0.2f, 0.3f));
		cube_program.set_uniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		cube_program.set_uniform("material.shininess", 32.0f);
		cube_program.set_uniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		cube_program.set_uniform("light.diffuse", light_diffuse);
		cube_program.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		cube_program.set_uniform("light.position", light_pos);
		cube_vao.draw(cube_program, GL_TRIANGLES, 0, 36);

		cube_light_maps_program.set_uniform("view", camera.get_view_matrix());
		cube_light_maps_program.set_uniform("projection", camera.get_projection_matrix());
		cube_light_maps_program.set_uniform("model",
			glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, -5.0f, -1.0f)) *
			glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()) * 2.0f, glm::vec3(0.7f, 0.33f, 0.0f))
			);
		cube_light_maps_program.set_uniform("viewPos", camera.get_position());
		cube_light_maps_program.set_uniform("material.diffuse", 0);
		cube_light_maps_program.set_uniform("material.specular", 1);
		cube_light_maps_program.set_uniform("material.shininess", 32.0f);
		cube_light_maps_program.set_uniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		cube_light_maps_program.set_uniform("light.diffuse", light_diffuse);
		cube_light_maps_program.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		cube_light_maps_program.set_uniform("light.position", light_pos);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,container_diffuse_tex.get_tex_id());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,container_specular_tex.get_tex_id());
		cube_with_light_maps_vao.draw(cube_light_maps_program, GL_TRIANGLES, 0, 36);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,0);

		for(int i = 0;i < 10;i++)
		{
			parallel_light_cube_program.set_uniform("view", camera.get_view_matrix());
			parallel_light_cube_program.set_uniform("projection", camera.get_projection_matrix());
			parallel_light_cube_program.set_uniform("model",
				glm::translate(glm::mat4(1.0f), glm::vec3(-20 - 5 * i, -5.0f, -1.0f)) *
				glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime() * (i + 1)) * 2.0f, glm::vec3(0.7f + i % 3, 0.33f + i % 2, 0.0f))
				);
			parallel_light_cube_program.set_uniform("viewPos", camera.get_position());
			parallel_light_cube_program.set_uniform("material.diffuse", 0);
			parallel_light_cube_program.set_uniform("material.specular", 1);
			parallel_light_cube_program.set_uniform("material.shininess", 32.0f);
			parallel_light_cube_program.set_uniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
			parallel_light_cube_program.set_uniform("light.diffuse", glm::vec3(1.0f,1.0f,1.0f));
			parallel_light_cube_program.set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
			parallel_light_cube_program.set_uniform("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,container_diffuse_tex.get_tex_id());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D,container_specular_tex.get_tex_id());
			cube_with_light_maps_vao.draw(parallel_light_cube_program, GL_TRIANGLES, 0, 36);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D,0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,0);
		}

		cube_light_maps_program.set_uniform("model",glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, -5.0f, 3.0f)));
		yoimiya_model.draw_model(cube_light_maps_program);

		glfwSwapBuffers(win);
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}

int main() noexcept
{
	try
	{
		run();
	}
	catch (std::exception& e)
	{
		std::cerr << std::format("Exception: {}", e.what()) << std::endl;
	}
}

// TODO: 放射光贴图
// https://learnopengl-cn.github.io/img/02/04/lighting_maps_exercise4.png