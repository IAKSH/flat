#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat
{
    class Physical
	{
	private:
		glm::mat4 position;
		glm::vec3 velocity;

	protected:
		bool checkHit(Physical& obj);

	public:
		const glm::mat4& getPositionMat();
		const glm::vec3& getVelocityVec();
		float getCentralPosX();
		float getCentralPosY();
		void transform(glm::mat4 trans);
		void updatePosition(float ms);
		void addVelocity(glm::vec3 vel);
		Physical();
		~Physical();
	};
}