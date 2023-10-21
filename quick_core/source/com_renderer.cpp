#include <quick_core/com_renderer.hpp>

void quick3d::core::Renderer::update_program_uniform() noexcept
{
	update_program_uniform_without_model();
	glm::mat4 rotate_matrix = glm::rotate(glm::mat4(1.0f), rotate_pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	rotate_matrix = glm::rotate(rotate_matrix, rotate_yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	rotate_matrix = glm::rotate(rotate_matrix, rotate_roll, glm::vec3(0.0f, 0.0f, 1.0f));

	program->set_uniform("model",
		glm::translate(glm::mat4(1.0f), glm::vec3(position_x, position_y, position_z)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale)) * 
		rotate_matrix
		);
}

void quick3d::core::Renderer::update_program_uniform_without_model() noexcept
{
	program->set_uniform("projection", camera->get_projection_matrix());
	program->set_uniform("view", camera->get_view_matrix());
}

quick3d::core::Renderer::Renderer() noexcept
	: position_x(0.0f), position_y(0.0f), position_z(0.0f), rotate_pitch(0.0f), rotate_yaw(0.0f), rotate_roll(0.0f), scale(0.001f)
{
}

void quick3d::core::Renderer::bind_camera(gl::FPSCamera* camera) noexcept
{
	this->camera = camera;
}

void quick3d::core::Renderer::bind_program(gl::Program* program) noexcept
{
	this->program = program;
}

float quick3d::core::Renderer::get_position_x() noexcept
{
	return position_x;
}

float quick3d::core::Renderer::get_position_y() noexcept
{
	return position_y;
}

float quick3d::core::Renderer::get_position_z() noexcept
{
	return position_z;
}

float quick3d::core::Renderer::get_rotate_pitch() noexcept
{
	return rotate_pitch;
}

float quick3d::core::Renderer::get_rotate_yaw() noexcept
{
	return rotate_yaw;
}

float quick3d::core::Renderer::get_rotate_roll() noexcept
{
	return rotate_roll;
}

void quick3d::core::Renderer::set_rotate_pitch(float f) noexcept
{
	rotate_pitch = f;
}

void quick3d::core::Renderer::set_rotate_yaw(float f) noexcept
{
	rotate_yaw = f;
}

void quick3d::core::Renderer::set_rotate_roll(float f) noexcept
{
	rotate_roll = f;
}

float quick3d::core::Renderer::get_sacle() noexcept
{
	return scale;
}

void quick3d::core::Renderer::set_position_x(float f) noexcept
{
	position_x = f;
}

void quick3d::core::Renderer::set_position_y(float f) noexcept
{
	position_y = f;
}

void quick3d::core::Renderer::set_position_z(float f) noexcept
{
	position_z = f;
}

void quick3d::core::Renderer::set_scale(float f) noexcept
{
	scale = f;
}

void quick3d::core::ModelRenderer::on_tick(float delta_ms) noexcept(false)
{
	update_program_uniform();
	model->draw_model(*program);
}

void quick3d::core::ModelRenderer::bind_model(gl::Model* model) noexcept
{
	this->model = model;
}

void quick3d::core::CubeMapVAORenderer::on_tick(float delta_ms) noexcept(false)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_cubemap_id());

	update_program_uniform();
	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void quick3d::core::CubeMapVAORenderer::bind_vbo(gl::Buffer* vbo) noexcept
{
	this->vbo = vbo;
}

void quick3d::core::CubeMapVAORenderer::bind_vao(gl::VertexArray* vao) noexcept
{
	this->vao = vao;
}

void quick3d::core::CubeMapVAORenderer::bind_cubemap(gl::CubeMap* cubemap) noexcept
{
	this->cubemap = cubemap;
}

void quick3d::core::SkyboxVAORenderer::update_skybox_program_uniform() noexcept
{
	program->set_uniform("projection", camera->get_projection_matrix());
	program->set_uniform("view", glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + camera->get_front_vec(), camera->get_up_vec()));
}

void quick3d::core::SkyboxVAORenderer::on_tick(float delta_ms) noexcept(false)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_cubemap_id());

	update_skybox_program_uniform();
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

	update_program_uniform();
	vao->draw(*program, GL_TRIANGLES, 0, vbo->get_buffer_size() / sizeof(float));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void quick3d::core::VAORenderer::bind_vao(gl::VertexArray* vao) noexcept
{
	this->vao = vao;
}

void quick3d::core::VAORenderer::bind_textures(gl::Texture* tex) noexcept
{
	textures.push_back(tex);
}

void quick3d::core::VAORenderer::bind_vbo(gl::Buffer* vbo) noexcept
{
	this->vbo = vbo;
}