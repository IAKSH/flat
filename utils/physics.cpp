#include "physics.hpp"

ni::utils::Rotatable::Rotatable()
    : right{1.0f,0.0f,0.0f},up{0.0f,1.0f,0.0f},orientation(glm::vec3(0.0f, 0.0f, -1.0f))
{
    updateVectors();
}

float ni::utils::Rotatable::getYaw() const
{
    return glm::eulerAngles(orientation)[0];
}

float ni::utils::Rotatable::getPitch() const
{
    return glm::eulerAngles(orientation)[1];
}

float ni::utils::Rotatable::getRoll() const
{
    return glm::eulerAngles(orientation)[2];
}

void ni::utils::Rotatable::rotate(float dUp,float dRight,float dRoll)
{
    glm::quat yawQuat = glm::angleAxis(glm::radians(dUp), right);
    glm::quat pitchQuat = glm::angleAxis(glm::radians(dRight), up);
    orientation = yawQuat * pitchQuat * orientation;
    updateVectors();
}

void ni::utils::Rotatable::updateVectors()
{
    glm::vec3 direction = glm::normalize(glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)));

    right = glm::normalize(glm::cross(direction, up));
    up = glm::normalize(glm::cross(right, direction));
}

void ni::utils::Rotatable::moveWithDirection(float dFront,float dRight,float dHeight)
{
    glm::vec3 position(getPositionX(),getPositionY(),getPositionZ());

    position += dFront * glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f)) + dRight * right + dHeight * up;

    setPositionX(position[0]);
    setPositionY(position[1]);
    setPositionZ(position[2]);
}