#include <quick_gl/camera.hpp>

quick3d::gl::Camera::Camera(glm::vec3 position, int viewport_width, int viewport_height,
    float yaw, float pitch, float roll, float fov, float near_plane, float far_plane) noexcept
    :   viewport_width(viewport_width),
        viewport_height(viewport_height),
        position(position),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        right(glm::vec3(1.0f, 0.0f, 0.0f)),
        up(glm::vec3(0.0f, 1.0f, 0.0f)),
        yaw(yaw),
        pitch(pitch),
        roll(roll),
        fov(fov),
        near_plane(near_plane),
        far_plane(far_plane)
{
}

void quick3d::gl::Camera::set_viewport_size(int width, int height) noexcept
{
    viewport_width = width;
    viewport_height = height;
}

void quick3d::gl::Camera::set_fov(float fov) noexcept
{
    this->fov = fov;
}

void quick3d::gl::Camera::set_near_plane(float near_plane) noexcept
{
    this->near_plane = near_plane;
}

void quick3d::gl::Camera::set_far_plane(float far_plane) noexcept
{
    this->far_plane = far_plane;
}

void quick3d::gl::Camera::set_position(glm::vec3 position) noexcept
{
    this->position = position;
}

void quick3d::gl::Camera::set_yaw(float yaw) noexcept
{
    this->yaw = yaw;
}

void quick3d::gl::Camera::set_pitch(float pitch) noexcept
{
    this->pitch = pitch;
}

void quick3d::gl::Camera::set_roll(float roll) noexcept
{
    this->roll = roll;
}

void quick3d::gl::Camera::move(float forward, float parallel, float vertical) noexcept
{
    position += front * forward + right * parallel + up * vertical;
}

void quick3d::gl::Camera::rotate(float yaw, float pitch, float roll) noexcept
{
    yaw += yaw;
    pitch += pitch;
    roll += roll;

    // Clamp pitch to avoid flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    update_camera_vectors();
}

float quick3d::gl::Camera::get_fov() const noexcept
{
    return fov;
}

float quick3d::gl::Camera::get_near_plane() const noexcept
{
    return near_plane;
}

float quick3d::gl::Camera::get_far_plane() const noexcept
{
    return far_plane;
}

float quick3d::gl::Camera::get_yaw() const noexcept
{
    return yaw;
}

float quick3d::gl::Camera::get_pitch() const noexcept
{
    return pitch;
}

float quick3d::gl::Camera::get_roll() const noexcept
{
    return roll;
}

glm::vec3 quick3d::gl::Camera::get_position() const noexcept
{
    return position;
}

glm::vec3 quick3d::gl::Camera::get_front_vec() const noexcept
{
    return front;
}

glm::vec3 quick3d::gl::Camera::get_up_vec() const noexcept
{
    return up;
}

glm::vec3 quick3d::gl::Camera::get_right_vec() const noexcept
{
    return right;
}

glm::mat4 quick3d::gl::Camera::get_view_matrix() const noexcept
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 quick3d::gl::Camera::get_projection_matrix() const noexcept
{
    return glm::perspective(glm::radians(fov), static_cast<float>(viewport_width) / static_cast<float>(viewport_height), near_plane, far_plane);
}

void quick3d::gl::Camera::update_camera_vectors() noexcept
{
    // Update front vector
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front);

    // Rotate front and up vectors around right vector for roll
    glm::mat4 roll_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(roll), right);
    front = glm::normalize(glm::vec3(roll_matrix * glm::vec4(front, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}