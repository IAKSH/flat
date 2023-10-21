#pragma once

#include <quick_ecs/com_renderer.hpp>

namespace quick3d::test::ecs_test
{
	class Skybox : public quick3d::ecs::Entity
	{
		using Renderer = quick3d::ecs::Renderer;

	private:
		inline static std::shared_ptr<Renderer> renderer;

		virtual void on_create() noexcept(false) final;
		virtual void on_destroy() noexcept(false) final;

	public:
		Skybox() = default;
		Skybox(Skybox&) = delete;
		~Skybox() = default;

		virtual void on_attach() noexcept(false) final;
		virtual void on_disattach() noexcept(false) final;
		virtual void on_tick(long long delta_ms) noexcept(false) final;
	};
}