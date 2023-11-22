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
		setup_camera();
	}
	catch (std::exception& e)
	{
		spdlog::critical("exception when initialize OESLayer:\n{}", e.what());
		std::terminate();
	}
}

void quick3d::test::OESLayer::setup_pipeline() noexcept(false)
{
	pipeline.add_pass<TestPass>(glsl_manager, camera);
}

void quick3d::test::OESLayer::setup_camera() noexcept
{
	camera.set_position(glm::vec3(0.0f, 0.0f, 1.0f));
	// TODO: 这个不能用，需要修
	//camera.rotate(-45.0f, 0.0f, 0.0f);
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

void quick3d::test::TestPass::load_character_model() noexcept(false)
{
	character_model = std::make_unique<gl::Model>("D:/Programming-Playground/quick3d/tests/light_ball/model/yoimiya/yoimiya.obj");
}

void quick3d::test::TestPass::load_cube_mesh() noexcept(false)
{
	cube_mesh = gl::gen_cube_mesh();
	cube_mesh->get_textures().push_back(new gl::MeshTexturePack("container2.png", "D:/Programming-Playground/quick3d/tests/light_ball/image", "texture_diffuse"));
}

quick3d::test::TestPass::TestPass(quick3d::gl::GLSLManager& glsl_manager, gl::Camera& camera) noexcept(false)
	: program(*glsl_manager.compile("test_pass.vs"), *glsl_manager.compile("test_pass.fs")), camera(camera)
{
	load_character_model();
	load_cube_mesh();
}

void quick3d::test::TestPass::exec() noexcept(false)
{
	// temp
	camera.move(-0.00001f, 0.0f, 0.0f);

	// temp
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	{
		auto scale_matrix{ glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f)) };
		auto model_matrix{ glm::rotate(scale_matrix, static_cast<float>(glfwGetTime()), glm::vec3(0.5f, 1.0f, -0.2f)) };
		program.set_uniform("pvm", camera.get_projection_matrix() * camera.get_view_matrix() * model_matrix);
		cube_mesh->draw_mesh(program);
	}
	{
		auto scale_matrix{ glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) };
		auto model_matrix{ glm::translate(scale_matrix,glm::vec3(0.0f,-1.0f,1.0f)) };
		program.set_uniform("pvm", camera.get_projection_matrix() * camera.get_view_matrix() * model_matrix);
		character_model->draw_model(program);
	}
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
