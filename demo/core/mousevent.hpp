#pragma once

#include "event.hpp"

namespace flat::core
{
	class MousePress : public Event
	{
	private:
		int glfwButtonCode;

	public:
		MousePress(int button)
			: glfwButtonCode(button)
		{
		}
		~MousePress() = default;
		int getGLFWButtonCode() { return glfwButtonCode; }
	};

	class MouseRelease : public MousePress
	{
	public:
		MouseRelease(int button)
			: MousePress(button)
		{
		}
		~MouseRelease() = default;
	};

	class MouseMove : public Event
	{
	private:
		int posX, posY;

	public:
		MouseMove(int x, int y)
			: posX(x),posY(y)
		{
		}
		~MouseMove() = default;
		int getPositionX() { return posX; }
		int getPositionY() { return posY; }
	};

	class MouseScroll : public Event
	{
	private:
		int offset;

	public:
		MouseScroll(int y)
			: offset(y)
		{
		}
		~MouseScroll() = default;
		int getOffset() { return offset; }
	};
}