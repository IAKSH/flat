#include <quick_core/com_mouse_input.hpp>

void quick3d::core::MousePositionInput::record_mouse_position() noexcept
{
	glfwGetCursorPos(win, &mouse_x, &mouse_y);
	mouse_delta_x = static_cast<float>(mouse_x - mouse_last_x);
	mouse_delta_y = static_cast<float>(mouse_y - mouse_last_y);
	mouse_last_x = mouse_x;
	mouse_last_y = mouse_y;
}

quick3d::core::MousePositionInput::MousePositionInput(GLFWwindow* win) noexcept
{
	if (win)
		this->win = win;
	else
		this->win = glfwGetCurrentContext();
}

float quick3d::core::MousePositionInput::get_mouse_delta_x() const noexcept
{
	return mouse_delta_x;
}

float quick3d::core::MousePositionInput::get_mouse_delta_y() const noexcept
{
	return mouse_delta_y;
}

double quick3d::core::MousePositionInput::get_mouse_x() const noexcept
{
	return mouse_x;
}

double quick3d::core::MousePositionInput::get_mouse_y() const noexcept
{
	return mouse_y;
}

void quick3d::core::MousePositionInput::on_tick(float delta_ms) noexcept
{
	record_mouse_position();
}

quick3d::core::MouseButtonInput::MouseButtonInput(GLFWwindow* win) noexcept
{
	if (win)
		this->win = win;
	else
		this->win = glfwGetCurrentContext();
}

bool quick3d::core::MouseButtonInput::check_mouse_button_pressed(int glfw_mouse_button) const noexcept
{
	return glfwGetMouseButton(win, glfw_mouse_button) == GLFW_PRESS;
}

bool quick3d::core::MouseButtonInput::check_mouse_button_hold(int glfw_mouse_button) const noexcept
{
	return glfwGetMouseButton(win, glfw_mouse_button) == GLFW_REPEAT;
}

void quick3d::core::MouseButtonInput::on_tick(float delta_ms) noexcept
{
}
