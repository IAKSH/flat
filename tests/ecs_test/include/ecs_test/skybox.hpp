#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	class SkyboxRenderer : public core::CubeMapVAORenderer
	{
	private:
		struct PhoneDirectLightingData
		{
			glm::vec4 direction;
			glm::vec4 ambient;
			glm::vec4 diffuse;
			glm::vec4 specular;
		};

		gl::Buffer phone_direct_lighting_ubo;
		void setup_phone_direct_lighting() noexcept;
		void load_shader_program() noexcept(false);
		void load_cubemap() noexcept(false);
		void load_vbo_vao() noexcept;

	public:
		SkyboxRenderer() noexcept(false);
		SkyboxRenderer(SkyboxRenderer&) = delete;
		~SkyboxRenderer() noexcept;
		void set_light_ambient(const glm::vec3& ambient) noexcept;
		void set_light_diffuse(const glm::vec3& diffuse) noexcept;
		void set_light_specular(const glm::vec3& specular) noexcept;
		void set_light_direction(const glm::vec3& direction) noexcept;
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
		void set_light_ambient(const glm::vec3& ambient) noexcept;
		void set_light_direction(const glm::vec3& direction) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
		virtual void on_draw(float delta_ms) noexcept(false) override final;
		virtual void on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false) override final;
	};
}