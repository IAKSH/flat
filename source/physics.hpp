#pragma once

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat
{
	class Physical
	{
	private:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 hitboxOffset;
		float hitboxScale = 1.0f;
		float rotate;
		float w, h;
		int gjKIterCount = 0;
		int gjk (const glm::vec2 * vertices1, size_t count1,const glm::vec2 * vertices2, size_t count2);
		float Perturbation();
		float dotProduct (glm::vec2 a, glm::vec2 b) { return a.x * b.x + a.y * b.y; }
		float lengthSquared (glm::vec2 v) { return v.x * v.x + v.y * v.y; }
		glm::vec2 subtract (glm::vec2 a, glm::vec2 b) { a.x -= b.x; a.y -= b.y; return a; }
		glm::vec2 negate (glm::vec2 v) { v.x = -v.x; v.y = -v.y; return v; }
		glm::vec2 perpendicular (glm::vec2 v) { glm::vec2 p = { v.y, -v.x }; return p; }
		glm::vec2 tripleProduct (glm::vec2 a, glm::vec2 b, glm::vec2 c);
		glm::vec2 averagePoint (const glm::vec2 * vertices, size_t count);
		glm::vec2 support (const glm::vec2 * vertices1, size_t count1,const glm::vec2 * vertices2, size_t count2, glm::vec2 d);
		glm::vec2 Jostle(glm::vec2 a);
		std::array<glm::vec2,4> getHitboxVertexCoords(Physical& obj);
		size_t indexOfFurthestPoint (const glm::vec2 * vertices, size_t count, glm::vec2 d);

	protected:
		Physical();
		~Physical();

	public:
		bool GJKCollisionCheck(Physical& obj);
		const glm::vec3 &getPositionVec();
		const glm::vec3 &getVelocityVec();
		const glm::vec3 &getHitboxOffset();
		float getPosX();
		float getPosY();
		float getRotate();
		const float &getSizeW();
		const float &getSizeH();
		const float &getHitboxScale();
		void setSizeW(float f);
		void setSizeH(float f);
		void setRotate(float f);
		void addRotate(float f);
		void setHitboxScale(float f);
		void addHitboxScale(float f);
		void setPosition(glm::vec3 &pos);
		void setPosition(glm::vec3 &&pos);
		void addPosition(glm::vec3 &vec);
		void addPosition(glm::vec3 &&vec);
		void updatePosition(float ms);
		void setVelocity(glm::vec3 &vel);
		void setVelocity(glm::vec3 &&vel);
		void addVelocity(glm::vec3 &vec);
		void addVelocity(glm::vec3 &&vec);
		void addHitboxOffset(glm::vec3 &vec);
		void addHitboxOffset(glm::vec3 &&vec);
		void setHitboxOffset(glm::vec3 &offset);
		void setHitboxOffset(glm::vec3 &&offset);
	};
}