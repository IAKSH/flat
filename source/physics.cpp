#include "physics.hpp"

#include <vector>

// 基于mat4 & 包围盒的碰撞检测
bool flat::Physical::checkHit(Physical& obj)
{
	// TODO
	return false;
}

const glm::mat4& flat::Physical::getPositionMat()
{
	return position;
}

const glm::vec3& flat::Physical::getVelocityVec()
{
	return velocity;
}

float flat::Physical::getCentralPosX()
{
	glm::vec3 translation = glm::vec3(position[3]);
	// 缩放因子
	glm::vec3 scale = glm::vec3(glm::length(glm::vec3(position[0])),
		glm::length(glm::vec3(position[1])),
		glm::length(glm::vec3(position[2])));
	glm::vec2 center = glm::vec2(translation.x, translation.y) / glm::vec2(scale[0], scale[1]);
	return center[0];
}

float flat::Physical::getCentralPosY()
{
	glm::vec3 translation = glm::vec3(position[3]);
	glm::vec3 scale = glm::vec3(glm::length(glm::vec3(position[0])),
		glm::length(glm::vec3(position[1])),
		glm::length(glm::vec3(position[2])));
	glm::vec2 center = glm::vec2(translation.x, translation.y) / glm::vec2(scale[0], scale[1]);
	return center[1];
}

void flat::Physical::transform(glm::mat4 trans)
{
	position *= trans;
}

void flat::Physical::updatePosition(float ms)
{
	glm::vec3 offset = velocity * ms;
	position *= glm::translate(glm::mat4(1.0f), offset);
}

void flat::Physical::addVelocity(glm::vec3 vel)
{
	velocity += vel;
}

flat::Physical::Physical()
{
    position[0] = glm::vec4(-0.5f,0.5f,0.0f,0.0f);
    position[1] = glm::vec4(0.5f,0.5f,0.0f,0.0f);
    position[2] = glm::vec4(0.5f,-0.5f,0.0f,0.0f);
    position[3] = glm::vec4(-0.5f,-0.5f,0.0f,0.0f);
}

flat::Physical::~Physical()
{

}