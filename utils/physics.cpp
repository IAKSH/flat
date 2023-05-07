#include "physics.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/quaternion_trigonometric.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

ni::utils::Rotatable::Rotatable()
    : right{1.0f,0.0f,0.0f},up{0.0f,1.0f,0.0f}
{
    glm::quat quat(glm::vec3(0.0f,0.0f,-1.0f));
    orientation = {quat[0],quat[1],quat[2],quat[3]};
    updateVectors();
}

float ni::utils::Rotatable::getYaw() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[0];
}

float ni::utils::Rotatable::getPitch() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[1];
}

float ni::utils::Rotatable::getRoll() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[2];
}

void ni::utils::Rotatable::rotate(float dUp,float dRight,float dRoll)
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vecRight(right[0],right[1],right[2]);
    glm::vec3 vecUp(up[0],up[1],up[2]);

    glm::quat yawQuat = glm::angleAxis(glm::radians(dUp), vecRight);
    glm::quat pitchQuat = glm::angleAxis(glm::radians(-dRight), vecUp);
    quat = yawQuat * pitchQuat * quat;

    orientation = {quat[0],quat[1],quat[2],quat[3]};
    right = {vecRight[0],vecRight[1],vecRight[2]};
    up = {vecUp[0],vecUp[1],vecUp[2]};

    updateVectors();
}

void ni::utils::Rotatable::updateVectors()
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vecRight(right[0],right[1],right[2]);
    glm::vec3 vecUp(up[0],up[1],up[2]);

    glm::vec3 direction = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
    vecRight = glm::normalize(glm::cross(direction, vecUp));
    vecUp = glm::normalize(glm::cross(vecRight, direction));

    orientation = {quat[0],quat[1],quat[2],quat[3]};
    right = {vecRight[0],vecRight[1],vecRight[2]};
    up = {vecUp[0],vecUp[1],vecUp[2]};
}

void ni::utils::Rotatable::moveWithDirection(float dFront,float dRight,float dHeight)
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vecRight(right[0],right[1],right[2]);
    glm::vec3 vecUp(up[0],up[1],up[2]);
    glm::vec3 position(getPositionX(),getPositionY(),getPositionZ());

    position += dFront * glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)) + dRight * vecRight + dHeight * vecUp;

    setPositionX(position[0]);
    setPositionY(position[1]);
    setPositionZ(position[2]);
}