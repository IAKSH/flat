#pragma once

#include <quick_core/entity.hpp>
#include <quick_gl/window.hpp>

namespace quick3d::core
{
	class MousePositionInput : public Component
	{
	private:
		GLFWwindow* win;
		double mouse_x, mouse_y;
		double mouse_last_x, mouse_last_y;
		float mouse_delta_x, mouse_delta_y;
		void record_mouse_position() noexcept;

	public:
		MousePositionInput(GLFWwindow* win = nullptr) noexcept;
		MousePositionInput(MousePositionInput&) = delete;
		~MousePositionInput() = default;
		float get_mouse_delta_x() const noexcept;
		float get_mouse_delta_y() const noexcept;
		double get_mouse_x() const noexcept;
		double get_mouse_y() const noexcept;
		virtual void on_tick(float delta_ms) noexcept override;
	};

	class MouseButtonInput : public Component
	{
	private:
		GLFWwindow* win;
	
	public:
		MouseButtonInput(GLFWwindow* win = nullptr) noexcept;
		MouseButtonInput(MouseButtonInput&) = delete;
		~MouseButtonInput() = default;
		bool check_mouse_button_pressed(int glfw_mouse_button) const noexcept;
		bool check_mouse_button_hold(int glfw_mouse_button) const noexcept;
		virtual void on_tick(float delta_ms) noexcept override;
	};
}