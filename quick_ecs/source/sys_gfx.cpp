#include <quick_ecs/sys_gfx.hpp>

#include <iostream>

quick3d::ecs::GfxSystem::GfxSystem(int w, int h, std::string_view title) noexcept
    : context(title, w, h), camera(w, h)
{
    on_create();
}

quick3d::ecs::GfxSystem::~GfxSystem() noexcept
{
    on_destroy();
}

void quick3d::ecs::GfxSystem::on_attach() noexcept(false)
{
    system_run();
}

void quick3d::ecs::GfxSystem::on_disattach() noexcept(false)
{
    system_stop();
}

void quick3d::ecs::GfxSystem::on_create() noexcept(false)
{
    bind_camera_to_context();
}

void quick3d::ecs::GfxSystem::on_destroy() noexcept(false)
{

}

void quick3d::ecs::GfxSystem::on_tick(float delta_ms) noexcept(false)
{
    // temp
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
        system_stop();

	camera.on_tick(delta_ms);

    context.swap_window_buffers();
    context.poll_events();
    //context.fill_frame_color(0.0f, 0.0f, 0.0f, 0.0f);
    context.clean_frame_buffers();
}

void quick3d::ecs::GfxSystem::bind_camera_to_context() noexcept
{
	context.get_window(0).set_mouse_callback([&](GLFWwindow* win, double x, double y)
	{ 
			camera.process_mouse_input(win, x, y); 
	});
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
		}
	});
}

quick3d::gl::FPSCamera& quick3d::ecs::GfxSystem::get_camera() noexcept
{
	return camera;
}

void quick3d::ecs::GfxSystem::capture_mouse() noexcept
{
	glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}