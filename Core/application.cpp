#include "application.hpp"
#include "pipe.hpp"
#include <exception>
#include <memory>

flat::Window::Window(std::string_view name)
    : window_name(name)
{
    if(!backends_initialized)
    {
        initialize_backends();
        backends_initialized = true;
    }
    else
        initialize_without_backends();
}

flat::Window::~Window()
{
    glfwDestroyWindow(window);
}

GLFWwindow* flat::Window::get_glfw_window()
{
    return window;
}

void flat::Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void flat::Window::process_event(Event&& e)
{
    if(event_callback)
        event_callback(std::move(e));
}

void flat::Window::set_position_x(int x)
{
    int buffer;
    glfwGetWindowPos(window,nullptr,&buffer);
    glfwSetWindowPos(window,x,buffer);
}

void flat::Window::set_position_y(int y)
{
    int buffer;
    glfwGetWindowPos(window,&buffer,nullptr);
    glfwSetWindowPos(window,buffer,y);
}

void flat::Window::set_width(int w)
{
    int buffer;
    glfwGetWindowSize(window,nullptr,&buffer);
    glfwSetWindowSize(window,w,buffer);
}

void flat::Window::set_height(int h)
{
    int buffer;
    glfwGetWindowSize(window,&buffer,nullptr);
    glfwSetWindowSize(window,buffer,h);
}

void flat::Window::set_title(std::string_view title)
{
    glfwSetWindowTitle(window,title.data());
}

int flat::Window::get_position_x()
{
    int x;
    glfwGetWindowPos(window,&x,nullptr);
    return x;
}

int flat::Window::get_position_y()
{
    int y;
    glfwGetWindowPos(window,nullptr,&y);
    return y;
}

int flat::Window::get_width()
{
    int w;
    glfwGetWindowSize(window,&w,nullptr);
    return w;
}

int flat::Window::get_height()
{
    int h;
    glfwGetWindowSize(window,nullptr,&h);
    return h;
}

std::string_view flat::Window::get_name()
{
    return window_name;
}

void flat::Window::initialize_backends()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback([](int error,const char* description){
        misc::main_logger->critical("GLFW error {}: {}",error,description);
        std::terminate();
    });

    initialize_without_backends();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        misc::main_logger->critical("Failed to initialize GLAD");
        std::terminate();
    }

    misc::main_logger->info("OpenGL info");
    misc::main_logger->info("|-- Vendor: {}", (const char*)glGetString(GL_VENDOR));
    misc::main_logger->info("|-- Renderer: {}", (const char*)glGetString(GL_RENDERER));
    misc::main_logger->info("`-- Version: {}", (const char*)glGetString(GL_VERSION));

    glfwSetWindowUserPointer(window,this);

    glfwSetWindowSizeCallback(window,[](GLFWwindow* window,int width,int height){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        win->process_event(WindowResizeEvent());
    });

    glfwSetWindowCloseCallback(window,[](GLFWwindow* window){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        win->process_event(WindowCloseEvent());
    });

    glfwSetKeyCallback(window,[](GLFWwindow* window,int key,int scancode,int action,int mods){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        switch(action)
        {
        case GLFW_REPEAT:
        case GLFW_PRESS:
            win->process_event(KeyButtomEvent(static_cast<KeyButtonCode>(key),KeyButtonStatus::Press));
            break;
        case GLFW_RELEASE:
            win->process_event(KeyButtomEvent(static_cast<KeyButtonCode>(key),KeyButtonStatus::Release));
            break;
        }
    });

    glfwSetMouseButtonCallback(window,[](GLFWwindow* window,int button,int action,int mods){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        switch(action)
        {
        case GLFW_PRESS:
            if(button == 0) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Press));
            else if(button == 1) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Press));
            else if(button == 2) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Press));
            break;
        case GLFW_RELEASE:
            if(button == 0) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Release));
            else if(button == 1) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Release));
            else if(button == 2) win->process_event(MouseButtonEvent(static_cast<MouseButtonCode>(button),MouseButtonStatus::Release));
            break;
        }
    });

    glfwSetScrollCallback(window,[](GLFWwindow* window,double offset_x,double offset_y){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        win->process_event(MouseScrollEvent(static_cast<float>(offset_x),static_cast<float>(offset_y)));
    });

    glfwSetCursorPosCallback(window,[](GLFWwindow* window,double pos_x,double pos_y){
        Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        win->process_event(MouseMoveEvent(static_cast<float>(pos_x),static_cast<float>(pos_y)));
    });
}

void flat::Window::initialize_without_backends()
{
    window = glfwCreateWindow(800,600,window_name.data(),nullptr,nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window,int width,int height){glViewport(0,0,width,height);});
}

flat::Mixer::Mixer()
{
    device = alcOpenDevice(nullptr);
    context = alcCreateContext(device,nullptr);
    alcMakeContextCurrent(context);
    
    ALenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        misc::main_logger->critical("OpenAL error: {}",alGetString(error));
        std::terminate();
    }
    alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
}

flat::Mixer::~Mixer()
{
    alcDestroyContext(context);
    alcCloseDevice(device);
}

ALCdevice* flat::Mixer::get_device()
{
    return device;
}

ALCcontext* flat::Mixer::get_context()
{
    return context;
}

flat::Application::Application()
    : should_quit(false),window("Unnamed")
{
    create_default_shader();
    create_default_camera();
}

flat::Application::~Application()
{
    for(auto& item : layers)
        item->on_detach();
}

void flat::Application::create_default_camera()
{
    // TODO: temp code
    default_camera = std::make_unique<Camera>(800,600);
    default_camera->set_position_z(1.0f);
}

void flat::Application::create_default_shader()
{
    default_shader = std::make_unique<opengl::ShaderProgram>(default_vertex_shader,default_fragment_shader);
    default_shader->active_texture("texture0",0);
}

void flat::Application::push_layer(std::unique_ptr<Layer> layer)
{
    layers.push_back(std::move(layer));
}

void flat::Application::push_overlay(std::unique_ptr<Layer> layer)
{
    for(auto& item : layers)
    {
        if(item->get_name() == layer->get_name())
        {
            item = std::move(layer);
            return;
        }
    }

    misc::main_logger->warn("push_overlay() can't match any layer with name \"{}\"",layer->get_name());
}

flat::Window& flat::Application::get_window()
{
    return window;
}

flat::Mixer& flat::Application::get_mixer()
{
    return mixer;
}

void flat::Application::exit()
{
    should_quit = true;
}

void flat::Application::run()
{
    for(auto& layer : layers)
        layer->on_attach();
    
    while(!should_quit)
    {
        for(auto& layer : layers)
        {
            layer->on_update();
            layer->on_render();
        }

        glfwPollEvents();
        glfwSwapBuffers(glfwGetCurrentContext());
    }
}

flat::Application& flat::Application::get_instance()
{
    static Application app;
    return app;
}

