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
		gl::Program* program;
		float position_x;
		float position_y;
		float position_z;
		float rotate_pitch;
		float rotate_yaw;
		float rotate_roll;
		float scale;

	public:
		Renderer() noexcept;
		Renderer(Renderer&) = delete;
		~Renderer() = default;
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