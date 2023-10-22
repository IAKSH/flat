#pragma once

#include <quick_core/entity.hpp>
#include <quick_gl/buffer.hpp>
#include <glm/matrix.hpp>

namespace quick3d::test
{
	class YaeEntity : public quick3d::core::Entity
	{
	private:
		inline static struct ModelData
		{
			glm::mat4 model[10];
		} model_data;
		//gl::Buffer ssbo_model;
		gl::Buffer ubo_model;

		void setup_model_data() noexcept;

	public:
		YaeEntity();
		YaeEntity(YaeEntity&) = delete;
		~YaeEntity() = default;
	};
}