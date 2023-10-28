#include <quick_core/com_keyboard_input.hpp>

quick3d::core::KeyboardInput::KeyboardInput(GLFWwindow* win) noexcept
{
	if (win)
		this->win = win;
	else
		this->win = glfwGetCurrentContext();
}

void quick3d::core::KeyboardInput::on_tick(float delta_ms) noexcept
{
}

bool quick3d::core::KeyboardInput::check_key_pressed(int glfw_keycode) const noexcept
{
	return glfwGetKey(win, glfw_keycode) == GLFW_PRESS;
}

bool quick3d::core::KeyboardInput::check_key_hold(int glfw_keycode) const noexcept
{
	return glfwGetKey(win, glfw_keycode) == GLFW_REPEAT;
}