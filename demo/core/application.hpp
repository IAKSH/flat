#pragma once

#include <deque>
#include <stack>

#include "window.hpp"
#include "layer.hpp"
#include "mixer.hpp"

namespace flat::core
{
	class Application
	{
	private:
		bool shouldExit;
		std::deque<Window*> windows;
		std::stack<Layer*> layers;
		Mixer* mixer;
		void bindInstance();
		void addMainWindow();
		void createMixer();
		void initialize();
		void release();
		static void forwardEvent(Event& event);

	public:
		Application();
        ~Application();

		void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);
		void run();
		void exit();

		static flat::core::Application* getInstance();
		friend void forwardEvent(Event& event);
	};

	
}