#include "camera.hpp"
#include "GLFW/glfw3.h"

flat::ni::Camera::Camera()
	: fov{ 45.0f }, aspectRatio{ 16.0f / 9.0f }, nearPlane{ 0.01f }, farPlane{ 100.0f }, yaw(0.0f), pitch(0.0f), zoom(0.0f),
	up{ 0.0f, 0.0f, 1.0f }, worldUp{ up }
{
	update();
}

glm::mat4 flat::ni::Camera::getTranslateMatrix()
{
	glm::vec3 position{ getPositionX(),getPositionY(),getPositionZ() };
	auto win = glfwGetCurrentContext();
	int h, w;
	glfwGetWindowSize(win, &w, &h);
	glm::mat4 projection = glm::perspective(glm::radians(fov + zoom), (float)w / (float)h, nearPlane, farPlane);
	return projection * glm::lookAt(position, position + front, up);
}

void flat::ni::Camera::move(float dforward, float dright)
{
	glm::vec3 position{ getPositionX(),getPositionY(),getPositionZ() };
	position += front * dforward;
	position += right * dright;
	setPositionX(position[0]);
	setPositionY(position[1]);
	setPositionZ(position[2]);
}
#include <iostream>
void flat::ni::Camera::turn(float upOffset, float rightOffset)
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

void flat::ni::Camera::update()
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

glm::mat4 flat::ni::Camera2D::getTranslateMatrix()
{
	GLFWwindow* win = glfwGetCurrentContext();
	int w, h;
	glfwGetWindowSize(win, &w, &h);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(w), 0.0f, static_cast<float>(h), -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-getPositionX() + w / 2, -getPositionY() + h / 2, 0.0f));
	return projection * view;
}