#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	class FloorRenderer : public core::VAORenderer
	{
	private:
		struct ModelData
		{
			glm::mat4 model[1];
		};
		gl::Buffer ssbo_model;

		gl::Buffer ebo;
		void setup_model_ssbo() noexcept;
		void load_shader_program() noexcept(false);
		void load_texture() noexcept(false);
		void load_vbo_vao() noexcept;
		void draw_indexed_vao() noexcept;
		void draw_indexed_vao(gl::Program& program) noexcept;

	public:
		FloorRenderer() noexcept(false);
		FloorRenderer(FloorRenderer&) = delete;
		~FloorRenderer() noexcept;
		void model_move(const glm::vec3& vec) noexcept;
		void model_rotate(float r, const glm::vec3& axis) noexcept;
		void switch_blinn_phong_lighting(bool b) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_tick(float delta_ms, gl::Program& program) noexcept(false) override final;
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
		void move(const glm::vec3& vec) noexcept;
		void rotate(float r, const glm::vec3& axis) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_draw(float delta_ms) noexcept(false) override final;
		virtual void on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false) override final;
	};
}