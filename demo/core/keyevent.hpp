#pragma once

#include "event.hpp"
#include "keycode.hpp"

namespace flat::core
{
	class KeyEvent : public Event
	{
	private:
		KeyCode keycode;

	public:
		KeyEvent(KeyCode code)
			: keycode(code)
		{
		}
		~KeyEvent() = default;
		KeyCode getKeyCode() { return keycode; }
	};

	class KeyPress : public KeyEvent
	{
	public:
		KeyPress(KeyCode code)
			: KeyEvent(code)
		{
		}
	};

	class KeyRelease : public KeyEvent
	{
	public:
		KeyRelease(KeyCode code)
			: KeyEvent(code)
		{
		}
	};
}