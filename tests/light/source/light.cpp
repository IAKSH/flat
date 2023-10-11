#include <array>
#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/light/glsl";

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

void run() noexcept(false)
{
	quick3d::gl::Context context("light test", SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	quick3d::gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

	quick3d::gl::Program cube_program(
		quick3d::gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"cube_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "cube_fs.glsl"))
	);

	quick3d::gl::Program light_program(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_vs.glsl")),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "light_fs.glsl"))
	);

	quick3d::gl::VBO cube_vbo(cube_vertices_with_normal);
	quick3d::gl::VAO cube_vao(cube_vbo);
	cube_vao.enable_attrib(0, 3, 6, 0);
	cube_vao.enable_attrib(1, 3, 6, 3);

	quick3d::gl::VBO light_vbo(cube_vertices);
	quick3d::gl::VAO light_vao(light_vbo);
	light_vao.enable_attrib(0, 3, 3, 0);

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

	auto win{ context.get_window(0).get_glfw_window() };
	while (!glfwWindowShouldClose(win))
	{
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		camera.on_tick(static_cast<float>(delta_time) * 10);

		// draw
		light_program.set_uniform("view", camera.get_view_matrix());
		light_program.set_uniform("projection", camera.get_projection_matrix());
		//light_program.set_uniform("scale", glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)));
		light_program.set_uniform("model", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		light_vao.draw(light_program, GL_TRIANGLES, 0, 36);

		cube_program.set_uniform("view", camera.get_view_matrix());
		cube_program.set_uniform("projection", camera.get_projection_matrix());
		//cube_program.set_uniform("scale", glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f)));
		cube_program.set_uniform("model",
			glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()), glm::vec3(sin(glfwGetTime()) * 10.0f, cos(glfwGetTime()) * 10.0f, 0.0f))
			);
		cube_program.set_uniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		cube_program.set_uniform("lightPos", glm::vec3(1.0f, 0.0f, 0.0f));
		cube_program.set_uniform("objectColor", glm::vec3(0.7f, 0.1f, 0.3f));
		cube_program.set_uniform("viewPos", camera.get_position());
		cube_vao.draw(cube_program, GL_TRIANGLES, 0, 36);

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