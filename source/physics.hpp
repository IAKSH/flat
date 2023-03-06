#pragma once

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
		float rotate;
		float w, h;

	protected:
		bool checkHit(Physical &obj);

	public:
		const glm::vec3 &getPositionVec();
		const glm::vec3 &getVelocityVec();
		float getPosX();
		float getPosY();
		float getRotate();
		const float &getSizeW();
		const float &getSizeH();
		void setSizeW(float f);
		void setSizeH(float f);
		void setRotate(float f);
		void addRotate(float f);
		void setPosition(glm::vec3 &pos);
		void setPosition(glm::vec3 &&pos);
		void addPosition(glm::vec3 &vec);
		void addPosition(glm::vec3 &&vec);
		void updatePosition(float ms);
		void setVelocity(glm::vec3 &vel);
		void setVelocity(glm::vec3 &&vel);
		void addVelocity(glm::vec3 &vec);
		void addVelocity(glm::vec3 &&vec);
		Physical();
		~Physical();
	};
}