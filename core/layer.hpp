#pragma once

#include <string>

#include "event.hpp"

namespace ni::core
{
	class Layer
	{
	private:
		std::string layerName;

	public:
		Layer(std::string_view name = "Layer")
			: layerName(name)
		{
		}
		~Layer() = default;

		std::string_view getName() { return layerName; }

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(Event& e) = 0;
	};
}