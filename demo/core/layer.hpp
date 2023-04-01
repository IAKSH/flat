#pragma once

// 引擎是由事件（Event）驱动的
// Layer是逻辑上的“层”，是用户填充代码的地方
// Application只有一个，其后端也只有一个，但是可以有多个Layer，Application产生Events，然后投递到每个Layer，执行相应代码
// 这个过程是即时的，没有消息队列。

#include <string_view>

#include "event.hpp"

namespace flat::core
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