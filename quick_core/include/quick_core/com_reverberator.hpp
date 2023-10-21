#pragma once

#include <array>
#include <quick_core/entity.hpp>
#include <quick_al/source.hpp>

namespace quick3d::core
{
	class Reverberator : Component
	{
	private:
		al::Source source;

	public:
		Reverberator() = default;
		Reverberator(Reverberator&) = delete;
		~Reverberator() = default;

		al::Source& get_source() noexcept;
		virtual void on_tick(float double_ms) noexcept(false) override final;
	};
}