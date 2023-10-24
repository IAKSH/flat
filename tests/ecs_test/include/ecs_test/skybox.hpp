#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	class SkyboxRenderer : public core::SkyboxVAORenderer
	{
	private:
		glm::vec3 phone_ambient;
		void setup_phone_ambient_value() noexcept;
		void load_shader_program() noexcept(false);
		void load_cubemap() noexcept(false);
		void load_vbo_vao() noexcept;

	public:
		SkyboxRenderer() noexcept(false);
		SkyboxRenderer(SkyboxRenderer&) = delete;
		~SkyboxRenderer() noexcept;

		void bind_camera(gl::FPSCamera* cam) noexcept;
	};

	class SkyboxEntity : public core::Entity
	{
	private:
		inline static std::shared_ptr< SkyboxRenderer> ren;
		void try_load_renderer() noexcept(false);

	public:
		SkyboxEntity(core::EntityManager& manager) noexcept(false);
		SkyboxEntity(SkyboxEntity&) = delete;
		~SkyboxEntity() = default;
		void bind_camera(gl::FPSCamera& cam) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}