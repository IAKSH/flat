#include "camera.hpp"

flat::ni::Camera::Camera()
	: fov{ 60.0f }, aspectRatio{ 16.0f / 9.0f }, nearPlane{ 0.01f }, farPlane{ 100.0f },
	front{ 1.0f,0.0f,0.0f }, up{ 0.0f,0.0f,1.0f }
{
}

glm::mat4 flat::ni::Camera::getTranslateMatrix()
{
	glm::vec3 position{ getPositionX(), getPositionY(), getPositionZ() };
	return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane) *
		glm::lookAt(position, position + front, up);
}

void flat::ni::Camera::move(float forward, float right)
{
	glm::vec3 position{ getPositionX(),getPositionY(),getPositionZ() };
	position += forward * front;
	position += right * glm::normalize(glm::cross(front, up));
	setPositionX(position[0]);
	setPositionY(position[1]);
	setPositionZ(position[2]);
}

void flat::ni::Camera::rotate(float rup,float rright)
{
	glm::vec3 position{ getPositionX(),getPositionY(),getPositionZ() };

	glm::mat4 rotateRight = glm::rotate(glm::mat4(1.0f), glm::radians(rright), up);
	front = glm::vec3(rotateRight * glm::vec4(front, 1.0f));

	glm::vec3 rightAxis = glm::cross(front, up);
	glm::mat4 rotateUp = glm::rotate(glm::mat4(1.0f), glm::radians(rup), rightAxis);
	front = glm::vec3(rotateUp * glm::vec4(front, 1.0f));
	up = glm::vec3(rotateUp * glm::vec4(up, 1.0f));
}
