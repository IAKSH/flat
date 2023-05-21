#include "physics.hpp"

flat::Rotator::Rotator()
    : right{1.0f,0.0f,0.0f},up{0.0f,1.0f,0.0f}
{
    glm::quat quat(glm::vec3(0.0f,0.0f,-1.0f));
    orientation = {quat[0],quat[1],quat[2],quat[3]};
    update_rotate_vector(*this);
}

flat::Rotator::~Rotator() = default;

float flat::Rotator::get_yaw() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[0];
}

float flat::Rotator::get_pitch() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[1];
}

float flat::Rotator::get_roll() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[2];
}