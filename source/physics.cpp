#include "physics.hpp"

#include <vector>

bool flat::Physical::checkHit(Physical& obj)
{
	// TODO
	return false;
}

const glm::vec3& flat::Physical::getPositionVec()
{
	return position;
}

const glm::vec3& flat::Physical::getVelocityVec()
{
	return velocity;
}

float flat::Physical::getPosX()
{
	return position[0];
}

float flat::Physical::getPosY()
{
	return position[1];
}

void flat::Physical::updatePosition(float ms)
{
	position += velocity * ms;
}

void flat::Physical::addVelocity(glm::vec3& vec)
{
	velocity += vec;
}

flat::Physical::Physical()
{

}

flat::Physical::~Physical()
{

}

const float& flat::Physical::getSizeH()
{
	return h;
}

const float& flat::Physical::getSizeW()
{
	return w;
}

void flat::Physical::setSizeH(float f)
{
	h = f;
}

void flat::Physical::setSizeW(float f)
{
	w = f;
}
