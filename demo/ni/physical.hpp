#pragma once

#include <glad/glad.h>
#include <AL/al.h>
#include <al/alc.h>

namespace flat::ni
{
	class MassPoint
	{
	private:
		float x, y, z;
		float vx, vy, vz;

	public:
		MassPoint()
			: x{ 0.0f }, y{ 0.0f }, z{ 0.0f }, vx{ 0.0f }, vy{ 0.0f }, vz{ 0.0f }
		{
		}
		~MassPoint() = default;

		const float& getPositionX() { return x; }
		const float& getPositionY() { return y; }
		const float& getPositionZ() { return z; }
		const float& getVelocityX() { return vx; }
		const float& getVelocityY() { return vy; }
		const float& getVelocityZ() { return vz; }
		void setPositionX(const float& val) { x = val; }
		void setPositionY(const float& val) { y = val; }
		void setPositionZ(const float& val) { z = val; }
		void setVelocityX(const float& val) { vx = val; }
		void setVelocityY(const float& val) { vy = val; }
		void setVelocityZ(const float& val) { vz = val; }
	};

	class Plane : public MassPoint
	{
	private:
		float w, h;
		float rx, ry, rz;

	public:
		Plane() {}
		~Plane() {}
		const float& getWidth() { return w; }
		const float& getHeight() { return h; }
		const float& getRotateX() { return rx; }
		const float& getRotateY() { return ry; }
		const float& getRotateZ() { return rz; }
		void setWidth(const float& val) { w = val; }
		void setHeight(const float& val) { h = val; }
		void setRotateX(const float& val) { rx = val; }
		void setRotateY(const float& val) { ry = val; }
		void setRotateZ(const float& val) { rz = val; }
	};

	bool collisionCheckGJK(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
}