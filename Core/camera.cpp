#include "object.hpp"

namespace flat
{
    std::unique_ptr<Camera> default_camera;
}

flat::Camera::Camera(int w,int h)
    : opengl::Camera(w,h)
{
}

flat::Camera::~Camera() = default;

void flat::Camera::set_position_x(float val)
{
    Point::set_position_x(val);
    update_listener();
}

void flat::Camera::set_position_y(float val)
{
    Point::set_position_y(val);
    update_listener();
}

void flat::Camera::set_position_z(float val)
{
    Point::set_position_z(val);
    update_listener();
}

void flat::Camera::set_velocity_x(float val)
{
    Velocitor::set_velocity_x(val);
    update_listener();
}

void flat::Camera::set_velocity_y(float val)
{
    Velocitor::set_velocity_y(val);
    update_listener();
}

void flat::Camera::set_velocity_z(float val)
{
    Velocitor::set_velocity_z(val);
    update_listener();
}

void flat::Camera::set_quat(const std::array<float,4>& arr)
{
    Rotatable::set_quat(arr);
    update_listener();
}

void flat::Camera::rotate(float d_up,float d_right,float d_roll)
{
    Rotatable::rotate(d_up,d_right,d_roll);
    update_listener();
}

void flat::Camera::move_with_direction(float d_front,float d_right,float d_height)
{
    Rotatable::move_with_direction(d_front,d_right,d_height);
    update_listener();
}