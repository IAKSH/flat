#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <GLFW/glfw3.h>

namespace quick3d::gl
{
    // 初始方向：-y
    // 注，引擎坐标系是 x,z,y
    class Camera
    {
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 up;
        float yaw;
        float pitch;
        float roll;
        float fov;
        float near_plane;
        float far_plane;
        int viewport_width;
        int viewport_height;

        void update_camera_vectors() noexcept;

    public:
        Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            int viewport_width = 800,
            int viewport_height = 600,
            float yaw = -90.0f,
            float pitch = 0.0f,
            float roll = 0.0f,
            float fov = 45.0f,
            float near_plane = 0.01f,
            float far_plane = 100.0f
        ) noexcept;
        ~Camera() = default;

        void set_viewport_size(int width, int height) noexcept;
        void set_fov(float fov) noexcept;
        void set_near_plane(float near_plane) noexcept;
        void set_far_plane(float far_plane) noexcept;
        void set_position(glm::vec3 position) noexcept;
        void set_yaw(float yaw) noexcept;
        void set_pitch(float pitch) noexcept;
        void set_roll(float roll) noexcept;
        void move(float forward, float parallel, float vertical) noexcept;
        void rotate(float yaw, float pitch, float roll) noexcept;
        float get_fov() const noexcept;
        float get_near_plane() const noexcept;
        float get_far_plane() const noexcept;
        float get_yaw() const noexcept;
        float get_pitch() const noexcept;
        float get_roll() const noexcept;
        glm::vec3 get_position() const noexcept;
        glm::vec3 get_front_vec() const noexcept;
        glm::vec3 get_up_vec() const noexcept;
        glm::vec3 get_right_vec() const noexcept;
        glm::mat4 get_view_matrix() const noexcept;
        glm::mat4 get_projection_matrix() const noexcept;
    };
}