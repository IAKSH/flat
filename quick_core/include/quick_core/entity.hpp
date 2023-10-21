#pragma once

#include <vector>

namespace quick3d::core
{
	class System
	{
	protected:
		bool running;

	public:
		System() noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) = 0;
		bool is_running() noexcept;
	};

	class Component
	{
	public:
		virtual void on_tick(float delta_ms) noexcept(false) = 0;
	};

	class Entity
	{
	protected:
		std::vector<Component*> components;

	public:
		virtual void on_tick(float delta_ms) noexcept(false);
		void bind_component(Component* com) noexcept;
	};
}