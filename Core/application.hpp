#pragma once

#include "event.hpp"
#include "layer.hpp"
#include "../../misc/disable_copy.hpp"
#include "../../misc/logger.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <functional>
#include <memory>
#include <string>
#include <deque>
#include <array>

namespace flat
{
    class Window : misc::DisableCopy
    {
        using EventCallBackFunc = std::function<void(Event&&)>;

    private:
        GLFWwindow* window;
        std::string window_name;
        EventCallBackFunc event_callback;
        void initialize_without_backends();
        void initialize_backends();
        inline static bool backends_initialized {false};

    public:
        Window(std::string_view name);
        ~Window();
        GLFWwindow* get_glfw_window();
        void update();
        void process_event(Event&& e);
        void set_position_x(int x);
        void set_position_y(int y);
        void set_height(int h);
        void set_width(int w);
        void set_title(std::string_view title);
        void set_event_callback(EventCallBackFunc func);
        int get_position_x();
        int get_position_y();
        int get_height();
        int get_width();
        std::string_view get_name();
    };

    class Mixer : misc::DisableCopy
    {
    private:
        ALCdevice* device;
        ALCcontext* context;

    public:
        Mixer();
        ~Mixer();
        ALCdevice* get_device();
        ALCcontext* get_context();
    };

    class Application : misc::DisableCopy
    {
    private:
        std::deque<std::unique_ptr<Layer>> layers;
        Window window;
        Mixer mixer;
        bool should_quit;

        static void forward_event(const Event& event);
        void create_default_shader();
        void create_default_camera();

    public:
        Application();
        ~Application();
        void push_layer(std::unique_ptr<Layer> layer);
        void push_overlay(std::unique_ptr<Layer> layer);
        Window& get_window();
        Mixer& get_mixer();
        void exit();
        void run();
        
        static Application& get_instance();
        friend void forward_event(const Event& event);
    };
}