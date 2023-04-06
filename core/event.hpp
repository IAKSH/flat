#pragma once

namespace ni::core
{
    enum class EventType
    {
        KeyPress,KeyRelease,
        MousePress,MouseRelease,MouseScroll,MouseMove,
        WindowClose,WindowFocus,WindowLostFocus,WindowResize,WindowMove,
        AppShutdown,AppStartup
    };

    class Event
	{
	private:
        EventType type;
		bool handled{ false };

    protected:
        void setType(EventType t) { type = t; }

	public:
        virtual ~Event() = default;
		bool getHandled() { return handled; }
		void setHandled(bool b) { handled = b; }
        EventType getType() {return type;}
	};
}