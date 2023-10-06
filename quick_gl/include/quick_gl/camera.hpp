#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>

namespace quick3d::gl
{
    class FPSCamera
    {
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        float yaw;
        float pitch;
        float movement_speed;
        float mouse_sensitivity;
        float fov;
        float near_plane;
        float far_plane;
        glm::vec2 last_mouse_position;
        int screen_width;
        int screen_height;
        bool move_right;
        bool move_left;
        bool move_forward;
        bool move_backward;

    public:
        FPSCamera(int screen_width, int screen_height, glm::vec3 start_pos = glm::vec3(0.0f, 0.0f, 0.0f), float start_yaw = -90.0f,
            float start_pitch = 0.0f, float speed = 2.5f, float sensitivity = 0.1f, float start_fov = 45.0f, float start_near = 0.1f,
            float start_far = 100.0f) noexcept
            : screen_width(screen_width), screen_height(screen_height), position(start_pos), front(glm::vec3(0.0f, 0.0f, -1.0f)),
              right(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(start_yaw), pitch(start_pitch),
              movement_speed(speed), mouse_sensitivity(sensitivity), fov(start_fov), near_plane(start_near), far_plane(start_far),
              last_mouse_position(0.0f, 0.0f)
        {
        }

        ~FPSCamera() = default;

        void process_keyboard_input(GLFWwindow* window, float delta_time) noexcept;
        void process_mouse_input(GLFWwindow* window, double x_pos, double y_pos) noexcept;

        void on_tick(float delta_time) noexcept;

        void set_viewport_size(int width, int height) noexcept;
        void set_fov(float fov) noexcept;
        void set_near_plane(float near_plane) noexcept;
        void set_far_plane(float far_plane) noexcept;
        void set_position(glm::vec3 position) noexcept;

        float get_fov() const noexcept;
        float get_near_plane() const noexcept;
        float get_far_plane() const noexcept;
        glm::vec3 get_position() const noexcept;
        glm::vec3 get_front_vec() const noexcept;
        glm::vec3 get_up_vec() const noexcept;
        glm::vec3 get_right_vec() const noexcept;

        glm::mat4 get_view_matrix() const noexcept;
        glm::mat4 get_projection_matrix() const noexcept;

    private:
        void update_camera_vectors() noexcept;
    };
}