#include "application.hpp"
#include "loggers.hpp"
#include <memory>

ni::core::Application::Application()
    : shoudQuit(false) 
{
    initialize();
}

ni::core::Application::~Application()
{
    release();
}

void ni::core::Application::configureWindow()
{
    window = std::make_unique<opengl::Window>("unnamed");
    window->setEventCallbackFunc(forwardEvent);
}

void ni::core::Application::configureMixer()
{
    mixer = std::make_unique<openal::Mixer>();
}

void ni::core::Application::initialize()
{
    configureWindow();
    configureMixer();
}

void ni::core::Application::release()
{
    AppShutdownEvent event;
    forwardEvent(event);

    for(auto& item : layers)
    item->onDetach();
}

void ni::core::Application::forwardEvent(Event& event)
{
    for(auto& item : getInstance().layers)
        item->onEvent(event);
}

void ni::core::Application::pushLayer(std::unique_ptr<Layer> layer)
{
    layers.push_back(std::move(layer));
}

void ni::core::Application::pushOverlay(std::unique_ptr<Layer> layer)
{
    // TODO
}

void ni::core::Application::exit()
{
    shoudQuit = true;
}

void ni::core::Application::run()
{
    for(auto& item : layers)
        item->onAttach();

    while (!shoudQuit)
    {
        for(auto& item : layers)
        {
            item->onUpdate();
            item->onRender();
        }

        glfwPollEvents();
        glfwSwapBuffers(glfwGetCurrentContext());
    }
}

ni::core::Application& ni::core::Application::getInstance()
{
    static Application app;
    return app;
}