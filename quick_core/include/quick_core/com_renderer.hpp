#pragma once

#include <quick_core/entity.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/cubemap.hpp>

namespace quick3d::core
{
	class Renderer : public Component
	{
	protected:
		gl::FPSCamera* camera;
		gl::Program* program;
		float position_x;
		float position_y;
		float position_z;
		float rotate_pitch;
		float rotate_yaw;
		float rotate_roll;
		float scale;

		void update_program_uniform() noexcept;
		void update_program_uniform_without_model() noexcept;

	public:
		Renderer() noexcept;
		Renderer(Renderer&) = delete;
		~Renderer() = default;
		void bind_camera(gl::FPSCamera* camera) noexcept;
		void bind_program(gl::Program* program) noexcept;
		float get_position_x() noexcept;
		float get_position_y() noexcept;
		float get_position_z() noexcept;
		float get_rotate_pitch() noexcept;
		float get_rotate_yaw() noexcept;
		float get_rotate_roll() noexcept;
		float get_sacle() noexcept;
		void set_position_x(float f) noexcept;
		void set_position_y(float f) noexcept;
		void set_position_z(float f) noexcept;
		void set_rotate_pitch(float f) noexcept;
		void set_rotate_yaw(float f) noexcept;
		void set_rotate_roll(float f) noexcept;
		void set_scale(float f) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override = 0;
	};

	class ModelRenderer : virtual public Renderer
	{
	protected:
		gl::Model* model;
		
	public:
		ModelRenderer() = default;
		ModelRenderer(ModelRenderer&) = delete;
		~ModelRenderer() = default;
		void bind_model(gl::Model* model) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class CubeMapVAORenderer : virtual public Renderer
	{
	protected:
		gl::Buffer* vbo;
		gl::VertexArray* vao;
		gl::CubeMap* cubemap;

	public:
		CubeMapVAORenderer() = default;
		CubeMapVAORenderer(CubeMapVAORenderer&) = delete;
		~CubeMapVAORenderer() = default;
		void bind_vbo(gl::Buffer* vbo) noexcept;
		void bind_vao(gl::VertexArray* vao) noexcept;
		void bind_cubemap(gl::CubeMap* cubemap) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class SkyboxVAORenderer : virtual public CubeMapVAORenderer
	{
	private:
		void update_skybox_program_uniform() noexcept;

	public:
		SkyboxVAORenderer() = default;
		SkyboxVAORenderer(SkyboxVAORenderer&) = delete;
		~SkyboxVAORenderer() = default;

		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class VAORenderer : virtual public Renderer
	{
	protected:
		gl::Buffer* vbo;
		gl::VertexArray* vao;
		std::vector<gl::Texture*> textures;
		
	public:
		VAORenderer() = default;
		VAORenderer(VAORenderer&) = delete;
		~VAORenderer() = default;
		void bind_vbo(gl::Buffer* vbo) noexcept;
		void bind_vao(gl::VertexArray* vao) noexcept;
		void bind_textures(gl::Texture* tex) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceRenderer : virtual public Renderer
	{
	protected:
		std::size_t instance_count;

	public:
		InstanceRenderer() noexcept;
		InstanceRenderer(InstanceRenderer&) = delete;
		~InstanceRenderer() = default;
		std::size_t get_instance_count() noexcept;
		void set_instance_count(std::size_t count) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override = 0;
	};

	class InstanceModelRenderer : virtual public ModelRenderer, virtual public InstanceRenderer
	{
	public:
		InstanceModelRenderer() = default;
		InstanceModelRenderer(InstanceModelRenderer&) = delete;
		~InstanceModelRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceCubeMapVAORenderer : virtual public CubeMapVAORenderer, virtual public InstanceRenderer
	{
	public:
		InstanceCubeMapVAORenderer() = default;
		InstanceCubeMapVAORenderer(InstanceCubeMapVAORenderer&) = delete;
		~InstanceCubeMapVAORenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceVAORenderer : virtual public VAORenderer, virtual public InstanceRenderer
	{
	public:
		InstanceVAORenderer() = default;
		InstanceVAORenderer(InstanceVAORenderer&) = delete;
		~InstanceVAORenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};
}