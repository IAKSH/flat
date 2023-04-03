#pragma once

#include "gameobject.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat::ni
{
	class Camera : public flat::ni::MassPoint
	{
	private:
		float fov;
		float aspectRatio;// 宽高比
		float nearPlane;// 近裁剪距离
		float farPlane;// 远裁剪距离
		glm::vec3 front;// 相机的方向向量
		glm::vec3 up;// 相机竖直方向的方向向量

	public:
		Camera();
		~Camera() = default;
		glm::mat4 getTranslateMatrix();
		const float& getFov() { return fov; }
		const float& getNearPlane() { return nearPlane; }
		const float& getFarPlane() { return farPlane; }
		const float& getFrontX() { return front[0]; }
		const float& getFrontY() { return front[1]; }
		const float& getFrontZ() { return front[2]; }
		const float& getUpX() { return up[0]; }
		const float& getUpY() { return up[1]; }
		const float& getUpZ() { return up[2]; }
		void setFov(const float& val) { fov = val; }
		void setNearPlane(const float& val) { nearPlane = val; }
		void setFarPlane(const float& val) { farPlane = val; }
		void setFrontX(const float& val) { front[0] = val; }
		void setFrontY(const float& val) { front[1] = val; }
		void setFrontZ(const float& val) { front[2] = val; }
		void setUpX(const float& val) { up[0] = val; }
		void setUpY(const float& val) { up[1] = val; }
		void setUpZ(const float& val) { up[2] = val; }

		void move(float forward,float right);
		void rotate(float rup,float rright);
	};
}