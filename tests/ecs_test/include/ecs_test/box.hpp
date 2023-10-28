#pragma once

#include <quick_core/com_renderer.hpp>
#include <random>
#include <array>

namespace quick3d::test
{
	class BoxRenderer : public core::InstanceVAORenderer
	{
	private:
		struct ModelData
		{
			glm::mat4 model[500];
		};
		gl::Buffer ssbo_model;

		struct ModelRotateAttrib
		{
			glm::vec3 rotate_axis;
			float rotate_speed;
		};
		std::array<ModelRotateAttrib,500> model_rotate_attribs;

		std::random_device rd;
		std::mt19937 gen;
		std::uniform_real_distribution<double> position_dis;
		std::uniform_real_distribution<double> rotation_dis;

		void setup_model_data(std::size_t index) noexcept;
		void rotate_model() noexcept;
		void load_shader_program() noexcept(false);
		void load_texture() noexcept(false);
		void load_vbo_vao() noexcept;

	public:
		BoxRenderer() noexcept(false);
		BoxRenderer(BoxRenderer&) = delete;
		~BoxRenderer() noexcept;
		void set_instance_count(int instance) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};

	class BoxEntity : public core::Entity
	{
	private:
		// TODO: 或许需要DI，renderer在外部实例化，然后在构造时传入
		// 但是这样EntityManager的转发会有问题
		inline static std::shared_ptr<BoxRenderer> ren;
		void try_load_renderer() noexcept(false);

	public:
		BoxEntity(core::EntityManager& manager) noexcept(false);
		BoxEntity(BoxEntity&) = delete;
		~BoxEntity() = default;
		void set_instance_count(int instance) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}