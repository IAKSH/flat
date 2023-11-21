#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

quick3d::test::OESLayer::OESLayer(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept(false)
	: window(title, window_w, window_h)
{
	initialize();
}

void quick3d::test::OESLayer::initialize() noexcept
{
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

void quick3d::test::OESLayer::setup_pipeline() noexcept(false)
{
	pipeline.add_pass<TestPass>(glsl_manager);
}

void quick3d::test::OESLayer::load_glsl() noexcept(false)
{
	glsl_manager.parse_from_file("../../../../tests/new_entity_sys/shader/test_pass.vs");
	glsl_manager.parse_from_file("../../../../tests/new_entity_sys/shader/test_pass.fs");
}

void quick3d::test::OESLayer::record_delta_time() noexcept
{
	double now_time = glfwGetTime();
	delta_sec = last_recored_time - now_time;
	last_recored_time = now_time;
}

void quick3d::test::OESLayer::exec() noexcept
{
	window.set_as_current();

	try
	{
		window.get_context().clean_frame_buffers();
		record_delta_time();
		pipeline.exec();
	}
	catch (std::exception& e)
	{
		spdlog::critical("exception in OESLayer:\n{}", e.what());
	}
}

quick3d::gl::Window& quick3d::test::OESLayer::get_window() noexcept
{
	return window;
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

void quick3d::test::Application::exec() noexcept
{
	while (true)
	{
		for (auto& layer : layers)
			layer->exec();
	}
}

void quick3d::test::DebugImGuiLayer::initialize_imgui() noexcept
{
	ImGui::CreateContext();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 320 es");
}

void quick3d::test::DebugImGuiLayer::begin_imgui() noexcept
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void quick3d::test::DebugImGuiLayer::draw_imgui() noexcept
{
	ImGui::Begin("Debug");
	ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
	ImGui::End();
}

void quick3d::test::DebugImGuiLayer::flush_imgui() noexcept
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void quick3d::test::DebugImGuiLayer::destroy_imgui() noexcept
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

quick3d::test::DebugImGuiLayer::DebugImGuiLayer() noexcept
{
	initialize_imgui();
}

quick3d::test::DebugImGuiLayer::~DebugImGuiLayer() noexcept
{
	destroy_imgui();
}

void quick3d::test::DebugImGuiLayer::exec() noexcept
{
	begin_imgui();
	draw_imgui();
	flush_imgui();
}

quick3d::test::WindowUpdateLayer::WindowUpdateLayer() noexcept
{

}

void quick3d::test::WindowUpdateLayer::add_context(gl::Window& window) noexcept
{
	this->windows.push_back(&window);
}

void quick3d::test::WindowUpdateLayer::exec() noexcept
{
	for (auto& window : windows)
		window->swap_buffers();

	glfwPollEvents();
}
