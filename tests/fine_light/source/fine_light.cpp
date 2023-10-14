#include <array>
#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/vertex.hpp>
#include <quick_gl/model.hpp>
#include <fine_light/obj_skybox.hpp>
#include <fine_light/obj_container.hpp>

static constexpr int SCR_WIDTH = 800;
static constexpr int SCR_HEIGHT = 600;

void run() noexcept(false)
{
	quick3d::gl::Context context("light test", SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	quick3d::gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

	quick3d::test::fine_light::Skybox skybox;
	std::vector<std::unique_ptr<quick3d::test::fine_light::Container>> containers;
	for(int i = 0;i < 5000;i++)
		containers.push_back(std::make_unique<quick3d::test::fine_light::Container>());

	context.get_window(0).set_mouse_callback([&](GLFWwindow* win, double x, double y)
		{ camera.process_mouse_input(win, x, y); });
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

		// draw skybox
		skybox.on_draw(camera);

		// draw container
		for(const auto& obj : containers)
			obj->on_draw(camera);

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