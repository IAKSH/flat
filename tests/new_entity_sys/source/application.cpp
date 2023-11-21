#include <new_entity_sys/application.hpp>
#include <spdlog/spdlog.h>

quick3d::test::OESLayer::OESLayer(gl::Window& window) noexcept(false)
	: window(window)
{
	window.set_as_current();
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
		spdlog::critical("exception when initialize OESLayer:\n{}", e.what());
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
		spdlog::critical("exception when OESLayer running:\n{}", e.what());
	}
}

quick3d::test::TestPass::TestPass(quick3d::gl::GLSLManager& glsl_manager) noexcept(false)
	: program(*glsl_manager.compile("test_pass.vs"), *glsl_manager.compile("test_pass.fs")),
	mesh(gl::gen_cube_mesh())
{
}

void quick3d::test::TestPass::exec() noexcept(false)
{
	auto scale{ glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) };
	program.set_uniform("model", glm::rotate(scale, static_cast<float>(glfwGetTime()), glm::vec3(0.5f, 1.0f, -0.2f)));
	mesh->draw_mesh(program);
}

void quick3d::test::Application::exec() noexcept
{
	while (true)
	{
		for (auto& layer : layers)
			layer->exec();
	}
}

void quick3d::test::ImGuiLayer::draw_imgui() noexcept
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Begin(title.data());
	ImGui::Text(" avg %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
}

void quick3d::test::ImGuiLayer::end_imgui() noexcept
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void quick3d::test::ImGuiLayer::destroy_imgui() noexcept
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void quick3d::test::ImGuiLayer::begin_imgui() noexcept
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

quick3d::test::ImGuiLayer::ImGuiLayer(ImGuiWindowLayer& window_layer, std::string_view title) noexcept
	: window(window_layer.get_window()), imgui_context(window_layer.get_imgui_context()), title(title)
{
}

quick3d::test::ImGuiLayer::~ImGuiLayer() noexcept
{
	destroy_imgui();
}

void quick3d::test::ImGuiLayer::exec() noexcept
{
	window.set_as_current();
	ImGui::SetCurrentContext(imgui_context);
	begin_imgui();
	draw_imgui();
	end_imgui();
}

void quick3d::test::WindowUpdateLayer::add_window(gl::Window& window) noexcept
{
	this->windows.push_back(&window);
}

void quick3d::test::WindowUpdateLayer::exec() noexcept
{
	for (auto& window : windows)
		window->swap_buffers();

	glfwPollEvents();
}

void quick3d::test::WindowLayer::correct_gl_viewport() noexcept
{
	int w, h;
	glfwGetWindowSize(window.get_glfw_window(), &w, &h);
	window.get_context().set_viewport(0, 0, w, h);
}

quick3d::test::WindowLayer::WindowLayer(std::string_view name, int w, int h) noexcept
	: window(name, w, h)
{
}

quick3d::gl::Window& quick3d::test::WindowLayer::get_window() noexcept
{
	return window;
}

void quick3d::test::WindowLayer::exec() noexcept
{
	window.set_as_current();
	correct_gl_viewport();
}

void quick3d::test::ImGuiWindowLayer::setup_imgui_context()
{
	window.set_as_current();
	IMGUI_CHECKVERSION();
	context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);
	ImGui_ImplGlfw_InitForOpenGL(window.get_glfw_window(), true);
	ImGui_ImplOpenGL3_Init("#version 320 es");

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui::StyleColorsDark();
}

quick3d::test::ImGuiWindowLayer::ImGuiWindowLayer(std::string_view name, int w, int h) noexcept
	: WindowLayer(name, w, h)
{
	setup_imgui_context();
}

ImGuiContext* quick3d::test::ImGuiWindowLayer::get_imgui_context() noexcept
{
	return context;
}
