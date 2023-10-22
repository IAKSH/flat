#include <ecs_test/entity_yae.hpp>
#include <glm/gtc/matrix_transform.hpp>

quick3d::test::YaeEntity::YaeEntity()
	: //ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_STATIC_DRAW, sizeof(model_data))
	ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_STATIC_DRAW, sizeof(model_data))
{
	setup_model_data();
}

void quick3d::test::YaeEntity::setup_model_data() noexcept
{
	/*
	for (int i = 0; i < 10; i++)
	{
		auto model{ glm::scale(glm::mat4(1.0f),glm::vec3(0.001f,0.001f,0.001f)) };
		model = glm::translate(model, glm::vec3(static_cast<float>(i) / 100.0f, 0.0f, 0.0f));
		model_data.model[i] = model;
	}
	ssbo_model.write_buffer_data(&model_data, 0, sizeof(model_data));
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
	*/

	auto model{ glm::scale(glm::mat4(1.0f),glm::vec3(0.001f,0.001f,0.001f)) };
	for (int i = 0; i < 10; i++)
		model_data.model[i] = glm::translate(model, glm::vec3(i, 0.0f, 0.0f));

	ssbo_model.write_buffer_data(&model_data, 0, sizeof(ModelData));
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
}