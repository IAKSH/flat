#include "application.hpp"

#include "log.hpp"

#include <functional>

static flat::core::Application* appInstance{ nullptr };

flat::core::Application* flat::core::Application::getInstance()
{
    if(appInstance)
        return appInstance;
    else
    {
        LOG_CRITICAL("Missing app instance");
        abort();
    }
}

flat::core::Application::Application()
    : shouldExit(false)
{
	initialize();
}

flat::core::Application::~Application()
{
	release();
}

void flat::core::Application::initialize()
{
    Log::init();
	bindInstance();
	addMainWindow();
}

void flat::core::Application::release()
{
    auto tempStack{ layers };
    while (!tempStack.empty())
    {
        tempStack.top()->onDetach();
        tempStack.pop();
    }
}

void flat::core::Application::forwardEvent(Event& event)
{
    auto tempStack{getInstance()->layers};
    while (!tempStack.empty())
    {
        tempStack.top()->onEvent(event);
        tempStack.pop();
    }
}

void flat::core::Application::bindInstance()
{
	if (!appInstance)
		appInstance = this;
	else
	{
		LOG_CRITICAL("Application instance conflict");
		abort();
	}
}

void flat::core::Application::addMainWindow()
{
	windows.push_back(new Window("MainWindow"));
    windows[0]->setEventCallbackFunc(forwardEvent);
}

void flat::core::Application::pushLayer(Layer* layer)
{
	layers.push(layer);
}

void flat::core::Application::pushOverlay(Layer* layer)
{
	// TODO
}

void flat::core::Application::run()
{
    // for each layer call onAttach
    auto tempStack{ layers };
    while (!tempStack.empty())
    {
        tempStack.top()->onAttach();
        tempStack.pop();
    }

    // main loop
    while (!shouldExit)
    {
        // TODO: Temp Code!!
        auto tempStack1{ layers };
        while (!tempStack1.empty())
        {
            tempStack1.top()->onUpdate();
            tempStack1.top()->onRender();
            tempStack1.pop();
        }
        glfwPollEvents();
        glfwSwapBuffers(glfwGetCurrentContext());
    }
}

void flat::core::Application::exit()
{
    shouldExit = true;
}
