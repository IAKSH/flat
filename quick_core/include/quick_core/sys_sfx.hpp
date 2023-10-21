#pragma once

#include <quick_core/entity.hpp>
#include <quick_al/context.hpp>

namespace quick3d::core
{
	class SFXSystem : public System
	{
	private:
		al::Device device;
		al::Context context;

	public:
		SFXSystem() noexcept(false);
		SFXSystem(std::string_view device_name) noexcept(false);
		SFXSystem(SFXSystem&) = delete;
		~SFXSystem() = default;

		virtual void on_tick(float delta_ms) noexcept(false) override;
	};
}