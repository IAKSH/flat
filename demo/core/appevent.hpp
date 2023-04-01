#pragma once

#include "event.hpp"

namespace flat::core
{
	struct TickEvent : Event
	{
	};

	struct UpdateEvent : Event
	{
	};

	struct RenderEvent : Event
	{
	};
}