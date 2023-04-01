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

	class EventDispatcher
	{
	private:
		Event& event;

	public:
		EventDispatcher(Event& e)
			: event(e)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// RTTI
			if (typeid(event) == typeid(F))
			{
				event.setHandled(func(static_cast<T&>(event)));
				return true;
			}
			return false;
		}
	};
}