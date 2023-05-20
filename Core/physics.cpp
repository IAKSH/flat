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

flat::Point::Point()
    : x(0),y(0),z(0)
{
}

flat::Point::Point(float x,float y,float z)
    : x(x),y(y),z(z)
{
}

float flat::Point::get_position_x() const
{
    return x;
}

float flat::Point::get_position_y() const
{
    return y;
}

float flat::Point::get_position_z() const
{
    return z;
}

void flat::Point::set_position_x(float val)
{
    x = val;
}

void flat::Point::set_position_y(float val)
{
    y = val;
}

void flat::Point::set_position_z(float val)
{
    z = val;
}

flat::Velocitor::Velocitor()
    : x(0),y(0),z(0)
{
}

flat::Velocitor::Velocitor(float x,float y,float z)
    : x(x),y(y),z(z)
{
}

float flat::Velocitor::get_velocity_x() const
{
    return x;
}

float flat::Velocitor::get_velocity_y() const
{
    return y;
}

float flat::Velocitor::get_velocity_z() const
{
    return z;
}

void flat::Velocitor::set_velocity_x(float val)
{
    x = val;
}

void flat::Velocitor::set_velocity_y(float val)
{
    y = val;
}

void flat::Velocitor::set_velocity_z(float val)
{
    z = val;
}

flat::Rotator::Rotator()
    : right{1.0f,0.0f,0.0f},up{0.0f,1.0f,0.0f}
{
    glm::quat quat(glm::vec3(0.0f,0.0f,-1.0f));
    orientation = {quat[0],quat[1],quat[2],quat[3]};
    update_vectors();
}

flat::Rotator::~Rotator() = default;

float flat::Rotator::get_rotate_yaw() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[0];
}

float flat::Rotator::get_rotate_pitch() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[1];
}

float flat::Rotator::get_rotate_roll() const
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    return glm::eulerAngles(quat)[2];
}

void flat::Rotator::set_quat(const std::array<float,4>& arr)
{
    orientation = arr;
}

void flat::Rotator::rotate(float d_up,float d_right,float d_roll)
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

void flat::Rotator::update_vectors()
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

void flat::Rotator::move(float d_front,float d_right,float d_height)
{
    glm::quat quat(orientation[0],orientation[1],orientation[2],orientation[3]);
    glm::vec3 vec_right(right[0],right[1],right[2]);
    glm::vec3 vec_up(up[0],up[1],up[2]);
    glm::vec3 position(point.get_position_x(),point.get_position_y(),point.get_position_z());

    position += d_front * glm::rotate(quat, glm::vec3(0.0f, 0.0f, -1.0f)) + d_right * vec_right + d_height * vec_up;

    point.set_position_x(position[0]);
    point.set_position_y(position[1]);
    point.set_position_z(position[2]);
}

flat::Square::Square(float x,float y,float z,float w,float h)
    : width(w),height(h)
{
    rotator.set_position_x(x);
    rotator.set_position_y(y);
    rotator.set_position_z(z);
}

flat::Square::Square()
    : Square(0.0f,0.0f,0.0f,1.0f,1.0f)
{ 
}

float flat::Square::get_square_width() const
{
    return width;
}

float flat::Square::get_square_height() const
{
    return height;
}

void flat::Square::set_square_width(float val)
{
    width = val;
}

void flat::Square::set_square_height(float val)
{
    height = val;
}

flat::Ball::Ball(float x,float y,float z,float r)
    : radius(r)
{
    set_position_x(x);
    set_position_y(y);
    set_position_z(z);
}

flat::Ball::Ball()
    : Ball(0.0f,0.0f,0.0f,1.0f)
{
}

float flat::Ball::get_radius() const
{
    return radius;
}

void flat::Ball::set_radius(float val)
{
    radius = val;
}