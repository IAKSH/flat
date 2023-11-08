#pragma once

#include <quick_core/com_renderer.hpp>
#include <random>
#include <array>

namespace quick3d::test
{
	class LightBallRenderer : public core::InstanceModelRenderer
	{
	private:
		struct ModelData
		{
			glm::mat4 model[500];
		};
		gl::Buffer ssbo_model;

		struct PositionData
		{
			glm::vec4 position[500];
		};
		gl::Buffer ssbo_position;

		struct InstanceCountData
		{
			int light_ball_instance;
		};
		gl::Buffer ssbo_instance_count;

		struct AttenuationData
		{
			float constant;
			float linear;
			float quadratic;
		};
		gl::Buffer ssbo_attenuation;

		struct ColorData
		{
			glm::vec4 color[500];
		};
		gl::Buffer ssbo_color;

		struct ModelMoveAttribs
		{
			glm::vec3 direction;
			float speed;
		};
		std::array<ModelMoveAttribs, 500> model_move_attribs;

		std::random_device rd;
		std::mt19937 gen;
		std::uniform_real_distribution<double> position_dis;
		std::uniform_real_distribution<double> move_direction_dis;

		void setup_color_data(int index) noexcept;
		void setup_model_data(int index) noexcept;
		void load_shader_program() noexcept(false);
		void load_model() noexcept(false);

	public:
		LightBallRenderer() noexcept(false);
		LightBallRenderer(LightBallRenderer&) = delete;
		~LightBallRenderer() noexcept;
		void set_instance_count(int instance) noexcept;
		void update_instance_position(float delta_ms) noexcept;
	};

	class LightBallEntity : public core::Entity
	{
	private:
		inline static std::shared_ptr<LightBallRenderer> ren;
		void try_load_renderer() noexcept(false);

	public:
		LightBallEntity(core::EntityManager& manager) noexcept(false);
		LightBallEntity(LightBallEntity&) = delete;
		~LightBallEntity() = default;
		void set_instance_count(int instance) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_draw(float delta_ms) noexcept(false) override final;
		virtual void on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false) override final;
	};
}