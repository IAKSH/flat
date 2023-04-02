#pragma once

namespace flat::core
{
	class Event
	{
	private:
		bool handled{ false };

	public:
		virtual ~Event() {}
		bool getHandled() { return handled; }
		void setHandled(bool b) { handled = b; }
	};
}