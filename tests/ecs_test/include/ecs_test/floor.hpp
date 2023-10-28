#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	class FloorRenderer : public core::VAORenderer
	{
	private:
		gl::Buffer ebo;
		void setup_model_matrix() noexcept;
		void load_shader_program() noexcept(false);
		void load_texture() noexcept(false);
		void load_vbo_vao() noexcept;
		void draw_indexed_vao() noexcept;

	public:
		FloorRenderer() noexcept(false);
		FloorRenderer(FloorRenderer&) = delete;
		~FloorRenderer() noexcept;
		void set_position(const glm::vec3& pos) noexcept;
		void switch_blinn_phong_lighting(bool b) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};

	class FloorEntity : public core::Entity
	{
	private:
		inline static std::shared_ptr<FloorRenderer> ren;
		void try_load_renderer() noexcept(false);

	public:
		FloorEntity(core::EntityManager& manager) noexcept(false);
		FloorEntity(FloorEntity&) = delete;
		~FloorEntity() = default;
		void switch_blinn_phong_lighting(bool b) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}