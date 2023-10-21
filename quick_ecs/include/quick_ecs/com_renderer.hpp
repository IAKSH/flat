#pragma once

#include <quick_ecs/sys_gfx.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/model.hpp>

// 关于 skybox
// 目前的架构完全无法实现 skybox
// 建议特例化，或者重新设计架构

namespace quick3d::ecs
{
	class DrawTarget
	{
	public:
		virtual void draw(gl::Program& program) noexcept = 0;
	};

	class ModelDrawTarget : public DrawTarget
	{
	private:
		gl::Model model;

	public:
		ModelDrawTarget(std::string_view path) noexcept;
		ModelDrawTarget(ModelDrawTarget&) = delete;
		~ModelDrawTarget() = default;

		virtual void draw(gl::Program& program) noexcept override final;
	};

	class VAODrawTarget : public DrawTarget
	{
	protected:
		gl::VertexArray vao;
		gl::Buffer vbo;
		std::size_t vertices_count;

		virtual void setup_vao(const void* data, std::size_t size) noexcept;

	public:
		VAODrawTarget(const void* data,std::size_t size) noexcept;
		VAODrawTarget(VAODrawTarget&) = delete;
		~VAODrawTarget() = default;

		virtual void draw(gl::Program& program) noexcept override;
	};

	class IndexedVAODrawTarget : public VAODrawTarget
	{
	private:
		gl::Buffer ebo;

		virtual void setup_vao(const void* data, std::size_t size) noexcept override final;

	public:
		IndexedVAODrawTarget(const void* vbo_data, std::size_t vbo_size, const void* ebo_data, std::size_t ebo_size) noexcept;
		IndexedVAODrawTarget(IndexedVAODrawTarget&) = delete;
		~IndexedVAODrawTarget() = default;
	};

	class SkyboxVAODrawTarget : public VAODrawTarget
	{
	protected:
		virtual void setup_vao(const void* data, std::size_t size) noexcept;

	public:
		SkyboxVAODrawTarget(const void* data, std::size_t size) noexcept;
	};

	// Renderer 渲染器
	// GLSL 管线（shader program）和可选的VAO，VBO，EBO集合
	// 使用 Renderer 即可进行绘图，也可以为Renderer绑定 Texture 或 Model 绘制复杂的结构
	// Renderer 会将一部分数据全局唯一存储（到sys_gfx) [待实现，数据加载目前直接在 Renderer 完成，以后可能会托管给其他类]
	// 可能会通过继承获得特化的渲染器

	// 有一个问题，就是 Shader Program 实际上是可能需要复用的，VAO，VBO，EBO也是
	// 但是相比之下，这点开销似乎问题不大

	class Renderer : public Component
	{
	protected:
		virtual void on_create() noexcept(false) override;
		virtual void on_destroy() noexcept(false) override;

		gl::FPSCamera& camera;
		std::vector<std::unique_ptr<DrawTarget>> targets;
		gl::Program program;

		float position_x;
		float position_y;
		float position_z;
		float rotate_pitch;	// TODO: not done yet
		float rotate_yaw;	// TODO: not done yet
		float rotate_roll;	// TODO: not done yet
		float scale;

		virtual void draw_each_target() noexcept;
		virtual void add_vao_target(const void* data,std::size_t size) noexcept(false);
		virtual void add_indexed_vao_target(const void* vbo_data, std::size_t vbo_size, const void* ebo_data, std::size_t ebo_size) noexcept(false);

	public:
		Renderer(gl::FPSCamera& camera, std::string_view vs, std::string_view fs) noexcept;
		Renderer(Renderer&) = delete;
		~Renderer() noexcept;

		virtual void on_attach() noexcept(false) override;
		virtual void on_disattach() noexcept(false) override;
		virtual void on_tick(float delta_ms) noexcept(false) override;

		void add_model_target(std::string_view path) noexcept(false);

		template <typename T,typename U = float>
		requires requires(T t)
		{
			{t.size()} -> std::same_as<std::size_t>;
			{t.data()} -> std::convertible_to<void*>;
		}
		void add_vao_target(const T& t) noexcept(false)
		{
			add_vao_target(t.data(), t.size() * sizeof(U));
		}

		template <typename T,typename U,typename V = float>
		requires requires(T t,U u)
		{
			{t.size()} -> std::same_as<std::size_t>;
			{t.data()} -> std::convertible_to<void*>;
			{u.size()} -> std::same_as<std::size_t>;
			{u.data()} -> std::convertible_to<void*>;
		}
		void add_indexed_vao_target(const T& t,const U& u) noexcept(false)
		{
			add_indexed_vao_target(t.data(), t.size() * sizeof(V), u.data(), u.size() * sizeof(unsigned int));
		}
	};

	class TextureRenderer : public Renderer
	{
	private:
		std::vector<std::unique_ptr<gl::Texture>> textures;
		virtual void draw_each_target() noexcept override;
	
	public:
		void add_texture(GLenum tex_format, std::string_view path) noexcept(false);
	};

	class CubemapRenderer : public Renderer
	{
	protected:
		gl::CubeMap cubemap;
		virtual void draw_each_target() noexcept override;

	public:
		CubemapRenderer(gl::FPSCamera& camera,
			std::string_view vs, std::string_view fs, GLenum tex_format, int cubemap_w, int cubemap_h) noexcept;
		void add_texture(GLenum location, std::string_view path) noexcept(false);
	};

	class SkyboxRenderer : public CubemapRenderer
	{
	private:
		virtual void draw_each_target() noexcept override;

	public:
		SkyboxRenderer(gl::FPSCamera& camera,
			std::string_view vs, std::string_view fs, GLenum tex_format, int cubemap_w, int cubemap_h) noexcept;

		virtual void add_vao_target(const void* data, std::size_t size) noexcept(false) override
		{
			targets.push_back(std::make_unique<SkyboxVAODrawTarget>(reinterpret_cast<const float*>(data), size));
		}

		virtual void add_indexed_vao_target(const void* vbo_data, std::size_t vbo_size, const void* ebo_data, std::size_t ebo_size) noexcept(false) override
		{
			// TODO: 糟糕，架构咬人了
			throw std::runtime_error("");
		}
	};
}