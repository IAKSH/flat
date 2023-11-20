#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

quick3d::test::Application::Application(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept
	: context(title, window_w, window_h)
{
	initialize();
}

void quick3d::test::Application::initialize() noexcept
{
	gl::set_current_context(context);

	try
	{
		load_glsl();
		setup_pipeline();
	}
	catch (std::exception& e)
	{
		spdlog::critical("exception when initialize Application:\n{}", e.what());
		std::terminate();
	}
}

void quick3d::test::Application::setup_pipeline() noexcept(false)
{
	pipeline.add_pass<TestPass>(glsl_manager);
}

void quick3d::test::Application::load_glsl() noexcept(false)
{
	glsl_manager.parse_from_file("../../../../tests/new_entity_sys/shader/test_pass.vs");
	glsl_manager.parse_from_file("../../../../tests/new_entity_sys/shader/test_pass.fs");
}

void quick3d::test::Application::record_delta_time() noexcept
{
	double now_time = glfwGetTime();
	delta_sec = last_recored_time - now_time;
	last_recored_time = now_time;
}

void quick3d::test::Application::run() noexcept
{
	try
	{
		GLFWwindow* win{ glfwGetCurrentContext() };
		while (!glfwWindowShouldClose(win))
		{
			record_delta_time();
			do_tick();
			pipeline.exec();
			glfwSwapBuffers(win);
			glfwPollEvents();
			gl::get_current_context().clean_frame_buffers();
		}
	}
	catch (std::exception& e)
	{
		spdlog::critical("exception when Application::run()!\n{}", e.what());
	}
}

void quick3d::test::Application::do_tick() noexcept(false)
{
	
}

quick3d::test::TestPass::TestPass(quick3d::gl::GLSLManager& glsl_manager) noexcept(false)
	: program(*glsl_manager.compile("test_pass.vs"), *glsl_manager.compile("test_pass.fs")),
	vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES))
{
	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);
}

void quick3d::test::TestPass::exec() noexcept(false)
{
	auto scale{ glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) };
	program.set_uniform("model", glm::rotate(scale, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f)));
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
}
