#include "camera.hpp"
#include "GLFW/glfw3.h"

ni::utils::Camera3D::Camera3D()
	: fov{ 45.0f }, aspectRatio{ 16.0f / 9.0f }, nearPlane{ 0.01f }, farPlane{ 100.0f }, yaw{0.0f}, pitch{0.0f}, zoom{0.0f},
	up{ 0.0f, 0.0f, 1.0f }, worldUp{ up }
{
	update();
}

glm::mat4 ni::utils::Camera3D::getTranslateMatrix()
{
	glm::vec3 position{ getPosX(),getPosY(),getPosZ() };
	auto win = glfwGetCurrentContext();
	int h, w;
	glfwGetWindowSize(win, &w, &h);
	glm::mat4 projection = glm::perspective(glm::radians(fov + zoom), (float)w / (float)h, nearPlane, farPlane);
	return projection * glm::lookAt(position, position + front, up);
}

void ni::utils::Camera3D::move(float dforward, float dright)
{
	glm::vec3 position{ getPosX(),getPosY(),getPosZ() };
	position += front * dforward;
	position += right * dright;
	setPosX(position[0]);
	setPosY(position[1]);
	setPosZ(position[2]);
}

void ni::utils::Camera3D::turn(float upOffset, float rightOffset)
{
	// Calculate the new front vector based on the current yaw and pitch
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Calculate the right and up vectors based on the current front vector and world up vector
	glm::vec3 newRight = glm::normalize(glm::cross(newFront, worldUp));
	glm::vec3 newUp = glm::normalize(glm::cross(newRight, newFront));

	// Rotate the up and right vectors by the specified offsets
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(upOffset), newRight);
	rotation = glm::rotate(rotation, glm::radians(rightOffset), newUp);
	up = glm::vec3(rotation * glm::vec4(up, 1.0f));
	right = glm::normalize(glm::cross(front, up)); // Recalculate right vector

	// Update the pitch and yaw values based on the new front vector
	pitch = glm::degrees(asin(newFront.y));
	yaw = glm::degrees(atan2(newFront.z, newFront.x));

	// Update the front vector based on the new pitch and yaw values
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
}

void ni::utils::Camera3D::update()
{
	// calculate new front vector using the updated Euler angles
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// update front, right and up vectors
	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 ni::utils::Camera2D::getTranslateMatrix() const
{
	GLFWwindow* win = glfwGetCurrentContext();
	int w, h;
	glfwGetWindowSize(win, &w, &h);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h), -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-getPosX() + w / 2.0f, -getPosY() + h / 2.0f, 0.0f));
	return projection * view;
}