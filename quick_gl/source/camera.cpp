#include <quick_gl/camera.hpp>

// may need tick duration count if you want accuracy
void quick3d::gl::FPSCamera::on_tick(float delta_time) noexcept
{
    float velocity = movement_speed * delta_time;
    if(move_forward)
        position += front * velocity;
    if(move_backward)
        position -= front * velocity;
    if(move_right)
        position += right * velocity;
    if(move_left)
        position -= right * velocity;

}

void quick3d::gl::FPSCamera::process_keyboard_input(GLFWwindow* window, float delta_time) noexcept
{
    float velocity = movement_speed * delta_time;
    
    move_forward = glfwGetKey(window, GLFW_KEY_W);
    move_backward = glfwGetKey(window,GLFW_KEY_S);
    move_right = glfwGetKey(window,GLFW_KEY_D);
    move_left = glfwGetKey(window,GLFW_KEY_A);
}

void quick3d::gl::FPSCamera::process_mouse_input(GLFWwindow* window, double x_pos, double y_pos) noexcept
{
    if (last_mouse_position.x == 0.0f && last_mouse_position.y == 0.0f) {
        last_mouse_position.x = static_cast<float>(x_pos);
        last_mouse_position.y = static_cast<float>(y_pos);
        return;
    }
    
    float xOffset = static_cast<float>(x_pos) - last_mouse_position.x;
    float yOffset = last_mouse_position.y - static_cast<float>(y_pos);  // Reversed since y-coordinates range from bottom to top
    
    last_mouse_position.x = static_cast<float>(x_pos);
    last_mouse_position.y = static_cast<float>(y_pos);

    xOffset *= mouse_sensitivity;
    yOffset *= mouse_sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Clamp pitch to avoid flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update front, right and up vectors
    update_camera_vectors();
}

void quick3d::gl::FPSCamera::set_viewport_size(int width, int height) noexcept
{
    screen_width = width;
    screen_height = height;
}

void quick3d::gl::FPSCamera::set_fov(float fov) noexcept
{
    this->fov = fov;
}

void quick3d::gl::FPSCamera::set_near_plane(float near_plane) noexcept
{
    this->near_plane = near_plane;
}

void quick3d::gl::FPSCamera::set_far_plane(float far_plane) noexcept
{
    this->far_plane = far_plane;
}

void quick3d::gl::FPSCamera::set_position(glm::vec3 position) noexcept
{
    this->position = position;
}

float quick3d::gl::FPSCamera::get_fov() const noexcept
{
    return fov;
}

float quick3d::gl::FPSCamera::get_near_plane() const noexcept
{
    return near_plane;
}

float quick3d::gl::FPSCamera::get_far_plane() const noexcept
{
    return far_plane;
}

glm::vec3 quick3d::gl::FPSCamera::get_position() const noexcept
{
    return position;
}

glm::vec3 quick3d::gl::FPSCamera::get_front_vec() const noexcept
{
    return front;
}

glm::vec3 quick3d::gl::FPSCamera::get_up_vec() const noexcept
{
    return up;
}

glm::vec3 quick3d::gl::FPSCamera::get_right_vec() const noexcept
{
    return right;
}

glm::mat4 quick3d::gl::FPSCamera::get_view_matrix() const noexcept
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 quick3d::gl::FPSCamera::get_projection_matrix() const noexcept
{
    return glm::perspective(glm::radians(fov), static_cast<float>(screen_width) / static_cast<float>(screen_height), near_plane, far_plane);
}

void quick3d::gl::FPSCamera::update_camera_vectors() noexcept
{
    // Calculate the new front vector
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front);
    
    // Calculate the new right and up vectors
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}