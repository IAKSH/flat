#pragma once

#include "event.hpp"
#include "../utils/template.hpp"
#include <string>

namespace ni::core
{
	class Layer : public utils::DisableCopy
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