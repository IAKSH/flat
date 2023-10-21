#include <quick_ecs/com_renderer.hpp>

void quick3d::ecs::Renderer::on_create() noexcept(false)
{

}

void quick3d::ecs::Renderer::on_destroy() noexcept(false)
{

}

quick3d::ecs::Renderer::Renderer(gl::FPSCamera& camera, std::string_view vs, std::string_view fs) noexcept
	: camera(camera), program(vs, fs), scale(0.01f), position_x(0.0f), position_y(0.0f), position_z(0.0f)
{
	on_create();
}

quick3d::ecs::Renderer::~Renderer() noexcept
{
	on_destroy();
}

void quick3d::ecs::Renderer::on_attach() noexcept(false)
{

}

void quick3d::ecs::Renderer::on_disattach() noexcept(false)
{

}

void quick3d::ecs::Renderer::on_tick(float delta_ms) noexcept(false)
{
	draw_each_target();
}

void quick3d::ecs::Renderer::draw_each_target() noexcept
{
	// TODO: 实现实例化
	// TODO: 使用SSBO优化相机的两个矩阵，实现每帧只传递一次相机矩阵

	auto projection{ camera.get_projection_matrix() };
	auto view{ camera.get_view_matrix() };
	auto model{
		glm::translate(glm::mat4(1.0f),glm::vec3(position_x,position_y,position_z)) *
		//glm::rotate(glm::mat4(1.0f),0.1f,glm::vec3(1.0f,1.0f,1.0f)) *
		glm::scale(glm::mat4(1.0f),glm::vec3(scale,scale,scale))
	};

	for (auto& target : targets)
	{
		program.set_uniform("projection", projection);
		program.set_uniform("view", view);
		program.set_uniform("model", model);
		target->draw(program);
	}
}

void quick3d::ecs::Renderer::add_vao_target(const void* data, std::size_t size) noexcept(false)
{
	targets.push_back(std::make_unique<VAODrawTarget>(data, size));
}

void quick3d::ecs::Renderer::add_indexed_vao_target(const void* vbo_data, std::size_t vbo_size, const void* ebo_data, std::size_t ebo_size) noexcept(false)
{
	targets.push_back(std::make_unique<IndexedVAODrawTarget>(vbo_data,
		vbo_size, ebo_data, ebo_size));
}

void quick3d::ecs::Renderer::add_model_target(std::string_view path) noexcept(false)
{
	targets.push_back(std::make_unique<ModelDrawTarget>(path));
}

quick3d::ecs::ModelDrawTarget::ModelDrawTarget(std::string_view path) noexcept
	: model(path)
{
}

void quick3d::ecs::ModelDrawTarget::draw(gl::Program& program) noexcept
{
	// TODO: 实现实例化
	model.draw_model(program);
}

void quick3d::ecs::VAODrawTarget::draw(gl::Program& program) noexcept
{
	// TODO: 实现实例化
	vao.draw(program, GL_TRIANGLES, 0, vertices_count);
}

quick3d::ecs::VAODrawTarget::VAODrawTarget(const void* data, std::size_t size) noexcept
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, size), vertices_count(size / sizeof(float))
{
	setup_vao(data, size);
}

void quick3d::ecs::SkyboxVAODrawTarget::setup_vao(const void* data, std::size_t size) noexcept
{
	vbo.write_buffer_data(data, 0, size);
	vao.add_attrib(vbo, 0, 3, 3, 0);
}

quick3d::ecs::SkyboxVAODrawTarget::SkyboxVAODrawTarget(const void* data, std::size_t size) noexcept
	: VAODrawTarget(data, size)
{
}

void quick3d::ecs::VAODrawTarget::setup_vao(const void* data, std::size_t size) noexcept
{
	vbo.write_buffer_data(data, 0, size);
	vao.add_attrib(vbo, 0, 3, 8, 0);
	vao.add_attrib(vbo, 1, 3, 8, 3);
	vao.add_attrib(vbo, 2, 2, 8, 6);
}

quick3d::ecs::IndexedVAODrawTarget::IndexedVAODrawTarget(
	const void* vbo_data, std::size_t vbo_size, const void* ebo_data, std::size_t ebo_size) noexcept
	: ebo(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, ebo_size), VAODrawTarget(vbo_data, vbo_size)
{
}

void quick3d::ecs::IndexedVAODrawTarget::setup_vao(const void* data, std::size_t size) noexcept
{
	vao.bind_ebo(ebo);
	VAODrawTarget::setup_vao(data, size);
}

void quick3d::ecs::TextureRenderer::add_texture(GLenum tex_format, std::string_view path) noexcept(false)
{
	textures.push_back(std::make_unique<gl::Texture>(tex_format, gl::Image(path)));
}

void quick3d::ecs::TextureRenderer::draw_each_target() noexcept
{
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->get_tex_id());
	}
	Renderer::draw_each_target();
	glActiveTexture(GL_TEXTURE0);
}

quick3d::ecs::CubemapRenderer::CubemapRenderer(gl::FPSCamera& camera,
	std::string_view vs, std::string_view fs, GLenum tex_format, int cubemap_w, int cubemap_h) noexcept
	: cubemap(tex_format, cubemap_w, cubemap_h), Renderer(camera, vs, fs)
{
}

void quick3d::ecs::CubemapRenderer::add_texture(GLenum location, std::string_view path) noexcept(false)
{
	cubemap.generate_texture(location, gl::Image(path, false));
}

void quick3d::ecs::CubemapRenderer::draw_each_target() noexcept
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.get_cubemap_id());
	Renderer::draw_each_target();
}

void quick3d::ecs::SkyboxRenderer::draw_each_target() noexcept
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.get_cubemap_id());

	auto projection{ camera.get_projection_matrix() };
	auto view{ camera.get_view_matrix() };

	for (auto& target : targets)
	{
		program.set_uniform("projection", projection);
		program.set_uniform("view", view);
		target->draw(program);
	}
}

quick3d::ecs::SkyboxRenderer::SkyboxRenderer(gl::FPSCamera& camera,
	std::string_view vs, std::string_view fs, GLenum tex_format, int cubemap_w, int cubemap_h) noexcept
	: CubemapRenderer(camera, vs, fs, tex_format, cubemap_w, cubemap_h)
{
}