#pragma once

#include "opengl_window.hpp"
#include "loggers.hpp"
#include "layer.hpp"
#include "mixer.hpp"
#include "event_application.hpp"
#include "template.hpp"
#include <deque>
#include <memory>

namespace ni::core
{
    using WindowBackends = Window<OpenGLWindow>;

    class Application : public DisableCopy
    {
    private:
        std::deque<std::unique_ptr<Layer>> layers;
        std::unique_ptr<WindowBackends> window;
        Mixer mixers;
        bool shoudQuit;

        void configureWindow()
        {
            window = std::make_unique<OpenGLWindow>("unnamed");
            window->setEventCallbackFunc(forwardEvent);
        }

		void initialize()
        {
            configureWindow();
        }

		void release()
        {
            AppShutdownEvent event;
            forwardEvent(event);

            for(auto& item : layers)
                item->onDetach();
        }

		static void forwardEvent(Event& event)
        {
            for(auto& item : getInstance().layers)
                item->onEvent(event);
        }

    public:
        Application() : shoudQuit(false) {initialize();}
        ~Application() {release();}

        void pushLayer(std::unique_ptr<Layer> layer) {layers.push_back(std::move(layer));}
        void pushOverlay(std::unique_ptr<Layer> layer) {/*TODO*/}
        void exit() {shoudQuit = true;}

		void run()
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

		static Application& getInstance()
        {
            static Application app;
            return app;
        }

		friend void forwardEvent(Event& event);
    };
}