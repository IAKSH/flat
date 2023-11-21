#include <quick_gl/window.hpp>


quick3d::gl::Window::Window(std::string_view title,int w,int h) noexcept
    : title(title)
{
    create_glfw_window(w,h);
}

quick3d::gl::Window::~Window() noexcept
{
    glfwDestroyWindow(window);
}

void quick3d::gl::Window::create_glfw_window(int w,int h) noexcept
{
    window = context.create_glfw_context(title, w, h);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window,this);

    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window,int width,int height)
    {
        glViewport(0,0,width,height);
    });

    glfwSetCursorPosCallback(window,[](GLFWwindow* win,double x,double y)
    {
        ((Window*)glfwGetWindowUserPointer(win))->try_run_mouse_movement_callback(x,y);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods)
    {
        ((Window*)glfwGetWindowUserPointer(win))->try_run_mouse_button_callback(button, action, mods);
    });

    glfwSetScrollCallback(window,[](GLFWwindow* win,double x,double y)
    {
        ((Window*)glfwGetWindowUserPointer(win))->try_run_scroll_callback(x,y);
    });

    glfwSetKeyCallback(window,[](GLFWwindow* win,int key,int scancode,int action,int mods)
    {
        ((Window*)glfwGetWindowUserPointer(win))->try_run_keyboard_callback(key,scancode,action,mods);
    });
}

void quick3d::gl::Window::set_as_current() noexcept
{
    if (glfwGetCurrentContext() != window)
        glfwMakeContextCurrent(window);
}

void quick3d::gl::Window::swap_buffers() noexcept
{
    glfwMakeContextCurrent(window);
    glfwSwapBuffers(window);
}

quick3d::gl::Context& quick3d::gl::Window::get_context() noexcept
{
    return context;
}

GLFWwindow* quick3d::gl::Window::get_glfw_window() const noexcept
{
    return window;
}

int quick3d::gl::Window::get_window_width() const noexcept
{
    int width;
    glfwGetWindowSize(window,&width,nullptr);
    return width;
}

int quick3d::gl::Window::get_window_height() const noexcept
{
    int height;
    glfwGetWindowSize(window,nullptr,&height);
    return height;
}

std::string_view quick3d::gl::Window::get_title() const noexcept
{
    return title;
}
        
void quick3d::gl::Window::try_run_keyboard_callback(int key,int scancode,int action,int mods) const noexcept
{
    if(keyboard_callback)
        keyboard_callback(window,key,scancode,action,mods);
}

void quick3d::gl::Window::try_run_mouse_movement_callback(double x,double y) const noexcept
{
    if(mouse_movement_callback)
        mouse_movement_callback(window,x,y);
}

void quick3d::gl::Window::try_run_mouse_button_callback(int button, int action, int mods) const noexcept
{
    if (mouse_button_callback)
        mouse_button_callback(window, button, action, mods);
}

void quick3d::gl::Window::try_run_scroll_callback(double x,double y) const noexcept
{
    if(scroll_callback)
        scroll_callback(window,x,y);
}

void quick3d::gl::Window::set_keybord_callback(const std::function<void(GLFWwindow*,int key,int scancode,int action,int mods)>& callback) noexcept
{
    keyboard_callback = callback;
}

void quick3d::gl::Window::set_mouse_movement_callback(const std::function<void(GLFWwindow*,double x,double y)>& callback) noexcept
{
    mouse_movement_callback = callback;
}

void quick3d::gl::Window::set_mouse_button_callback(const std::function<void(GLFWwindow*, int button, int action, int mods)>& callback) noexcept
{
    mouse_button_callback = callback;
}

void quick3d::gl::Window::set_scroll_callback(const std::function<void(GLFWwindow*,double x,double y)>& callback) noexcept
{
    scroll_callback = callback;
}