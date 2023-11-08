#pragma once

#include <quick_core/com_renderer.hpp>
#include <array>

namespace quick3d::test
{
	class WoodBoxRenderer : public core::VAORenderer
	{
	private:
		struct ModelData
		{
			glm::mat4 model[1];
		};
		gl::Buffer ssbo_model;

		void setup_model_data(std::size_t index) noexcept;
		void load_shader_program() noexcept(false);
		void load_texture() noexcept(false);
		void load_vbo_vao() noexcept;

	public:
		WoodBoxRenderer() noexcept(false);
		WoodBoxRenderer(WoodBoxRenderer&) = delete;
		~WoodBoxRenderer() noexcept;
		void set_instance_count(int instance) noexcept;
		void switch_blinn_phong_lighting(bool b) noexcept;
		void rotate_model(float delta_ms) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_tick(float delta_ms, gl::Program& program) noexcept(false) override final;
	};

	class WoodBoxEntity : public core::Entity
	{
	private:
		// TODO: 或许需要DI，renderer在外部实例化，然后在构造时传入
		// 但是这样EntityManager的转发会有问题
		inline static std::shared_ptr<WoodBoxRenderer> ren;
		void try_load_renderer() noexcept(false);

	public:
		WoodBoxEntity(core::EntityManager& manager) noexcept(false);
		WoodBoxEntity(WoodBoxEntity&) = delete;
		~WoodBoxEntity() = default;
		void set_instance_count(int instance) noexcept;
		void switch_blinn_phong_lighting(bool b) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_draw(float delta_ms) noexcept(false) override final;
		virtual void on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false) override final;
	};
}