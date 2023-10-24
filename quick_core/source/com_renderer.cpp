#include <quick_core/com_renderer.hpp>

quick3d::core::Renderer::Renderer() noexcept
	: position_x(0.0f), position_y(0.0f), position_z(0.0f), rotate_pitch(0.0f), rotate_yaw(0.0f), rotate_roll(0.0f), scale(0.001f)
{
}

void quick3d::core::ModelRenderer::on_tick(float delta_ms) noexcept(false)
{
	model->draw_model(*program);
}

void quick3d::core::CubeMapVAORenderer::on_tick(float delta_ms) noexcept(false)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_cubemap_id());

	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void quick3d::core::VAORenderer::on_tick(float delta_ms) noexcept(false)
{
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->get_tex_id());
	}

	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::core::InstanceRenderer::InstanceRenderer() noexcept
	: instance_count(1)
{
}

void quick3d::core::InstanceModelRenderer::on_tick(float delta_ms) noexcept(false)
{
	model->draw_model(*program, instance_count);
}

void quick3d::core::InstanceCubeMapVAORenderer::on_tick(float delta_ms) noexcept(false)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_cubemap_id());

	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float), instance_count);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void quick3d::core::InstanceVAORenderer::on_tick(float delta_ms) noexcept(false)
{
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->get_tex_id());
	}

	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float), instance_count);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}