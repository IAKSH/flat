#include "physics.hpp"
#include "glm/gtc/quaternion.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

flat::Rotatable::Rotatable()
    : right{1.0f,0.0f,0.0f},up{0.0f,1.0f,0.0f}
{
    glm::quat quat(glm::vec3(0.0f,0.0f,-1.0f));
    orientation = {quat[0],quat[1],quat[2],quat[3]};
    update_vectors();
}

float flat::Rotatable::get_yaw() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[0];
}

float flat::Rotatable::get_pitch() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[1];
}

float flat::Rotatable::get_roll() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[2];
}

void flat::Rotatable::rotate(float d_up,float d_right,float d_roll)
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vec_right(right[0],right[1],right[2]);
    glm::vec3 vec_up(up[0],up[1],up[2]);

    glm::quat yaw_quat = glm::angleAxis(glm::radians(d_up),vec_right);
    glm::quat pitch_quat = glm::angleAxis(glm::radians(-d_right),vec_up);
    quat = yaw_quat * pitch_quat * quat;

    orientation = {quat[0],quat[1],quat[2],quat[3]};
    right = {vec_right[0],vec_right[1],vec_right[2]};
    up = {vec_up[0],vec_up[1],vec_up[2]};

    update_vectors();
}

void flat::Rotatable::update_vectors()
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vec_right(right[0],right[1],right[2]);
    glm::vec3 vec_up(up[0],up[1],up[2]);

    glm::vec3 direction = glm::normalize(glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)));
    vec_right = glm::normalize(glm::cross(direction, vec_up));
    vec_up = glm::normalize(glm::cross(vec_right, direction));

    orientation = {quat[0],quat[1],quat[2],quat[3]};
    right = {vec_right[0],vec_right[1],vec_right[2]};
    up = {vec_up[0],vec_up[1],vec_up[2]};
}

void flat::Rotatable::move_with_direction(float d_front,float d_right,float d_height)
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vec_right(right[0],right[1],right[2]);
    glm::vec3 vec_up(up[0],up[1],up[2]);
    glm::vec3 position(get_position_x(),get_position_y(),get_position_z());

    position += d_front * glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)) + d_right * vec_right + d_height * vec_up;

    set_position_x(position[0]);
    set_position_y(position[1]);
    set_position_z(position[2]);
}