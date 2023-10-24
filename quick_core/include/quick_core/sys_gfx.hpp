#pragma once

#include <quick_core/entity.hpp>
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

		struct CameraUBOData
		{
			glm::mat4 projection;
			glm::mat4 view;
			glm::mat4 view_without_movement;
		};
		quick3d::gl::Buffer camera_ubo;

		void bind_camera_to_context() noexcept;
		void update_camera_ubo() noexcept;

	public:
		GFXSystem(int w, int h, std::string_view title = "Quick3D") noexcept(false);
		GFXSystem(GFXSystem&) = delete;
		~GFXSystem() = default;

		gl::FPSCamera& get_camera() noexcept;
		void capture_mouse(bool b = true) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}