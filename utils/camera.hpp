#pragma once

#include "mass_point.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ni::utils
{
    class Camera2D : public MassPoint
    {
    public:
        Camera2D() = default;
        ~Camera2D() = default;
        glm::mat4 const getTranslateMatrix() const;
    };

    // bad
    class Camera3D : public Camera2D
    {
        private:
		float fov;
		float aspectRatio;// 宽高比
		float nearPlane;// 近裁剪距离
		float farPlane;// 远裁剪距离
		float yaw;
		float pitch;
		//float roll;
		float zoom;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

	public:
		Camera3D();
		~Camera3D() = default;
		glm::mat4 getTranslateMatrix();
		const float& getFov() { return fov; }
		const float& getNearPlane() { return nearPlane; }
		const float& getFarPlane() { return farPlane; }
		const float& getYaw() { return yaw; }
		const float& getPitch() { return pitch; }
		void setFov(const float& val) { fov = val; }
		void setNearPlane(const float& val) { nearPlane = val; }
		void setFarPlane(const float& val) { farPlane = val; }
		void setYaw(const float& val) { yaw = val; }
		void setPitch(const float& val) { pitch = val; }
		void setZoom(const float& val) { zoom = val; }

		void move(float dForward, float dRight);
		void turn(float dPitch, float dYaw);
		void update();
    };
}