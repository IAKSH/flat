#include "application.hpp"
#include "../utils/logger.hpp"
#include <memory>
#include <exception>

namespace ni::core
{
    static Application* instance {nullptr};
}

ni::core::Application::Application()
    : shoudQuit{false}
{
    initialize();
}

ni::core::Application::~Application()
{
    release();
}

void ni::core::Application::bindInstance()
{
    if(!instance)
        instance = this;
    else
	{
        utils::coreLogger()->critical("application instance conflict");
		std::terminate();
	}
}

void ni::core::Application::addMainWindow()
{
    windows.push_back(std::make_unique<Window>("MainWindow"));
    windows[0]->setEventCallbackFunc(forwardEvent);
}

void ni::core::Application::addMainMixer()
{
    mixers.push_back(std::make_unique<Mixer>());
}

void ni::core::Application::initialize()
{
    addMainWindow();
    addMainMixer();
    bindInstance();
}

void ni::core::Application::release()
{
    AppShutdownEvent event;
    forwardEvent(event);

    for(auto& item : layers)
        item->onDetach();
}

ni::core::Application* ni::core::Application::getInstance()
{
    return instance;
}

void ni::core::Application::forwardEvent(Event& event)
{
    for(auto& item : getInstance()->layers)
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

void ni::core::Application::exit()
{
    shoudQuit = true;
}
