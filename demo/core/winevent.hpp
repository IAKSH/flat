#pragma once

#include "event.hpp"

namespace flat::core
{
	struct WindowClose : public Event
	{
	};

	struct WindowFocus : public Event
	{
	};

	struct WindowLostFocus : public Event
	{
	};

	class WindowResize : public Event
	{
	private:
		int width, height;

	public:
		WindowResize(int w, int h)
			: width(w), height(h)
		{
		}
		~WindowResize() = default;
		int getWidth() { return width; }
		int getHeight() { return height; }
	};

	class WindowMove : public Event
	{
	private:
		int posX, posY;

	public:
		WindowMove(int x, int y)
			: posX(x), posY(y)
		{
		}
		~WindowMove() = default;
		int getPositionX() { return posX; }
		int getPositionY() { return posY; }
	};
}