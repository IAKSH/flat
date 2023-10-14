#include <array>
#include <thread>
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
#include <fine_light/obj_light_ball.hpp>
#include <fine_light/obj_yoimiya.hpp>

//#define __MULTI_THREAD_TEST__

static constexpr int SCR_WIDTH = 1920;
static constexpr int SCR_HEIGHT = 1080;

void run() noexcept(false)
{
	quick3d::gl::Context context("fine light test", SCR_WIDTH, SCR_HEIGHT);
	glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	quick3d::gl::FPSCamera camera(SCR_WIDTH, SCR_HEIGHT);

	quick3d::test::fine_light::Skybox skybox;

	std::vector<std::unique_ptr<quick3d::test::fine_light::Object>> objects;
	std::vector<std::unique_ptr<quick3d::test::fine_light::LightBall>> light_balls;
	std::vector<std::unique_ptr<quick3d::test::fine_light::Container>> containers;
	std::vector<std::unique_ptr<quick3d::test::fine_light::Yoimiya>> yoimiyas;
	for(int i = 0;i < 10;i++)
		containers.push_back(std::make_unique<quick3d::test::fine_light::Container>());
	for(int i = 0;i < 10;i++)
		yoimiyas.push_back(std::make_unique<quick3d::test::fine_light::Yoimiya>());
	for(int i = 0;i < 250;i++)
		light_balls.push_back(std::make_unique<quick3d::test::fine_light::LightBall>());
	for(auto& light_ball : light_balls)
		quick3d::test::fine_light::Container::add_light_ball(light_ball.get());
	for(auto& light_ball : light_balls)
		quick3d::test::fine_light::Yoimiya::add_light_ball(light_ball.get());
	for(auto& container : containers)
		objects.push_back(std::move(container));
	for(auto& yoimiya : yoimiyas)
		objects.push_back(std::move(yoimiya));
	for(auto& light_ball : light_balls)
		objects.push_back(std::move(light_ball));

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

	// Multi-thread test
#ifdef __MULTI_THREAD_TEST__
	std::thread t0([&]()
	{
		while(true)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(6));
			current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			if(delta_time > 0.006)
			{
				last_frame = current_frame;
				camera.on_tick(static_cast<float>(delta_time) * 10);

				// obj on_tick
				for(const auto& obj : objects)
					obj->on_tick(delta_time);
			}
		}
	});
	t0.detach();
#endif

	auto win{ context.get_window(0).get_glfw_window() };
	while (!glfwWindowShouldClose(win))
	{
#ifndef __MULTI_THREAD_TEST__
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		camera.on_tick(static_cast<float>(delta_time) * 10);

		// obj on_tick
		for(const auto& obj : objects)
			obj->on_tick(delta_time);
#endif

		// draw skybox
		skybox.on_draw(camera);
		// draw obj
		for(const auto& obj : objects)
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