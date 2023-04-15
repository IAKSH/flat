#pragma once

#include <deque>
#include <memory>

#include "layer.hpp"
#include "window.hpp"
#include "mixer.hpp"
#include "event_application.hpp"

namespace ni::core
{
    class Application
    {
    private:
        std::deque<std::unique_ptr<Layer>> layers;
        std::deque<std::unique_ptr<Window>> windows;
        std::deque<std::unique_ptr<Mixer>> mixers;
        bool shoudQuit;
        void bindInstance();
		void addMainWindow();
		void addMainMixer();
		void initialize();
		void release();
		static void forwardEvent(Event& event);

    public:
        Application();
        Application(Application&) = delete;
        ~Application();

        void pushLayer(std::unique_ptr<Layer> layer);
        void pushOverlay(std::unique_ptr<Layer> layer);
		void run();
		void exit();

		static Application* getInstance();
		friend void forwardEvent(Event& event);
    };
}