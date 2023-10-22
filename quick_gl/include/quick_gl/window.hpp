#pragma once

#include <string>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace quick3d::gl
{
    class Window
    {
    private:
        GLFWwindow* window;
        // GLFW don't have API to get window's title, so we store it by ourselves
        // https://discourse.glfw.org/t/get-the-title-of-an-existing-window/744
        std::string title;
        std::function<void(GLFWwindow*,double x,double y)> mouse_movement_callback;
        std::function<void(GLFWwindow*, int button, int action, int mods)> mouse_button_callback;
        std::function<void(GLFWwindow*,double x,double y)> scroll_callback;
        std::function<void(GLFWwindow*,int key,int scancode,int action,int mods)> keyboard_callback;

        void create_glfw_window(int w,int h) noexcept;

    public:
        Window(std::string_view title,int w,int h) noexcept;

        Window(Window&) = delete;

        ~Window() noexcept;

        GLFWwindow* get_glfw_window() const noexcept;
        int get_window_width() const noexcept;
        int get_window_height() const noexcept;
        std::string_view get_title() const noexcept;
        void try_run_keyboard_callback(int key,int scancode,int action,int mods) const noexcept;
        void try_run_mouse_movement_callback(double x,double y) const noexcept;
        void try_run_mouse_button_callback(int button, int action, int mods) const noexcept;
        void try_run_scroll_callback(double x,double y) const noexcept;
        void set_keybord_callback(const std::function<void(GLFWwindow*,int key,int scancode,int action,int mods)>& callback) noexcept;
        void set_mouse_movement_callback(const std::function<void(GLFWwindow*,double x,double y)>& callback) noexcept;
        void set_mouse_button_callback(const std::function<void(GLFWwindow*, int button, int action, int mods)>& callback) noexcept;
        void set_scroll_callback(const std::function<void(GLFWwindow*,double x,double y)>& callback) noexcept;
    };
}