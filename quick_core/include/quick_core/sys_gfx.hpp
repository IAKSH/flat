#pragma once

#include <quick_core/entity.hpp>
#include <quick_core/com_mouse_input.hpp>
#include <quick_core/com_keyboard_input.hpp>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>
#include <quick_gl/buffer.hpp>

namespace quick3d::core
{
	class GFXSystem : public System
	{
	private:
		gl::Context context;
		gl::FPSCamera camera;
		bool mouse_caputured;

		struct GFXGlobalUBO
		{
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 view_without_movement;
			glm::mat4 sun_lightspace_matrix;
			glm::vec4 camera_position;
			float gamma;
			int global_enable_point_shadow;
			int global_enable_direct_shadow;
		};
		quick3d::gl::Buffer gfx_global_ubo;

		MousePositionInput mouse_pos_input;
		MouseButtonInput mouse_button_input;
		KeyboardInput keyboard_input;

		void bind_gfx_global_ubo() noexcept;
		void update_camera(float delta_ms) noexcept;
		void update_camera_ubo() noexcept;
		void enable_full_screen() noexcept;

	public:
		GFXSystem(int w, int h, std::string_view title = "Quick3D") noexcept(false);
		GFXSystem(GFXSystem&) = delete;
		~GFXSystem() = default;

		gl::FPSCamera& get_camera() noexcept;
		gl::Context& get_context() noexcept;
		void capture_mouse(bool b = true) noexcept;
		void set_gamma(float gamma) noexcept;
		void set_lightspace_matrix(const glm::mat4& matrix) noexcept;
		void switch_point_shadow(bool b) noexcept;
		void switch_direct_shadow(bool b) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}