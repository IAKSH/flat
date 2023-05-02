#pragma once

#include "opengl_window.hpp"
#include "openal_mixer.hpp"
#include "layer.hpp"
#include "event_application.hpp"
#include "template.hpp"
#include <deque>
#include <memory>

namespace ni::core
{
    using WindowBackends = Window<opengl::Window>;
    using MixerBackends = Mixer<openal::Mixer>;

    class Application : public DisableCopy
    {
    private:
        std::deque<std::unique_ptr<Layer>> layers;
        std::unique_ptr<WindowBackends> window;
        std::unique_ptr<MixerBackends> mixer;
        bool shoudQuit;

        void configureWindow();
        void configureMixer();
		void initialize();
		void release();

		static void forwardEvent(Event& event);

    public:
        Application();
        ~Application();

        void pushLayer(std::unique_ptr<Layer> layer);
        void pushOverlay(std::unique_ptr<Layer> layer);
        void exit();
		void run();

		static Application& getInstance();
		friend void forwardEvent(Event& event);
    };
}