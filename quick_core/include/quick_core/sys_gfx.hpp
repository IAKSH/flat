#pragma once

#include <quick_core/entity.hpp>
#include <quick_gl/context.hpp>
#include <quick_gl/camera.hpp>

namespace quick3d::core
{
	class GFXSystem : public System
	{
	private:
		gl::Context context;
		gl::FPSCamera camera;

		void bind_camera_to_context() noexcept;

	public:
		GFXSystem(int w, int h, std::string_view title = "Quick3D") noexcept(false);
		GFXSystem(GFXSystem&) = delete;
		~GFXSystem() = default;

		gl::FPSCamera& get_camera() noexcept;
		void capture_mouse() noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}