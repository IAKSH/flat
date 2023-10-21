#include <quick_core/sys_gfx.hpp>

quick3d::core::GFXSystem::GFXSystem(int w, int h, std::string_view title) noexcept(false)
    : context(title, w, h), camera(w, h)
{
    bind_camera_to_context();
}

void quick3d::core::GFXSystem::on_tick(float delta_ms) noexcept(false)
{
    // temp
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
        running = false;

    camera.on_tick(delta_ms);
    context.swap_window_buffers();
    context.poll_events();
    context.clean_frame_buffers();
}

void quick3d::core::GFXSystem::bind_camera_to_context() noexcept
{
    context.get_window(0).set_mouse_callback([&](GLFWwindow* win, double x, double y) { camera.process_mouse_input(win, x, y); });
    context.get_window(0).set_keybord_callback([&](GLFWwindow* win, int key, int scancode, int action, int mods)
        {
            camera.process_keyboard_input(win, 0.001f);

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
}

void quick3d::core::GFXSystem::capture_mouse() noexcept
{
    glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

quick3d::gl::FPSCamera& quick3d::core::GFXSystem::get_camera() noexcept
{
    return camera;
}