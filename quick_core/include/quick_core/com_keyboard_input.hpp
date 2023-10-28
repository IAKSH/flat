#pragma once

#include <quick_core/entity.hpp>
#include <quick_gl/window.hpp>

namespace quick3d::core
{
	class KeyboardInput : Component
	{
	private:
		GLFWwindow* win;

	public:
		KeyboardInput(GLFWwindow* win = nullptr) noexcept;
		KeyboardInput(KeyboardInput&) = delete;
		~KeyboardInput() = default;
		bool check_key_pressed(int glfw_keycode) const noexcept;
		bool check_key_hold(int glfw_keycode) const noexcept;
		virtual void on_tick(float delta_ms) noexcept override final;
	};
}