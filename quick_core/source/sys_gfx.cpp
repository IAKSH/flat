#include <quick_core/sys_gfx.hpp>

quick3d::core::GFXSystem::GFXSystem(int w, int h, std::string_view title) noexcept(false)
    : context(title, w, h), camera(w, h), mouse_caputured(false), gfx_global_ubo(GL_UNIFORM_BUFFER, GL_STREAM_DRAW, sizeof(GFXGlobalUBO))
{
    bind_camera_to_context();
    bind_gfx_global_ubo();
    set_gamma(2.2f);
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

    update_camera_ubo();
}

void quick3d::core::GFXSystem::bind_camera_to_context() noexcept
{
    // TODO: 需要构建一个独立的键鼠事件系统
    context.get_window(0).set_mouse_movement_callback([&](GLFWwindow* win, double x, double y)
    {
        if(mouse_caputured)
            camera.process_mouse_input(win, x, y);
    });

    context.get_window(0).set_keybord_callback([&](GLFWwindow* win, int key, int scancode, int action, int mods)
        {
            camera.process_keyboard_input(win, 0.1f);

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

    context.get_window(0).set_mouse_button_callback([&](GLFWwindow* win, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            if (button == GLFW_MOUSE_BUTTON_RIGHT)
                capture_mouse((mouse_caputured = !mouse_caputured));
        }
    });
}

void quick3d::core::GFXSystem::bind_gfx_global_ubo() noexcept
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, gfx_global_ubo.get_buffer_id());
}

void quick3d::core::GFXSystem::update_camera_ubo() noexcept
{
    gfx_global_ubo.dma_do([&](void* data)
    {
        auto ptr{ reinterpret_cast<GFXGlobalUBO*>(data) };
        ptr->projection = get_camera().get_projection_matrix();
        ptr->view = get_camera().get_view_matrix();
        ptr->view_without_movement = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + camera.get_front_vec(), camera.get_up_vec());
        ptr->camera_position = glm::vec4(get_camera().get_position(), 1.0f);
    });
}

void quick3d::core::GFXSystem::capture_mouse(bool b) noexcept
{
    if (b)
        glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(context.get_window(0).get_glfw_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void quick3d::core::GFXSystem::set_gamma(float gamma) noexcept
{
    gfx_global_ubo.dma_do([&](void* data)
    {
        auto ptr{ reinterpret_cast<GFXGlobalUBO*>(data) };
        ptr->gamma = gamma;
    });
}

quick3d::gl::FPSCamera& quick3d::core::GFXSystem::get_camera() noexcept
{
    return camera;
}