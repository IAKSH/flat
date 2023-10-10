#pragma once

#include <cstdint>
#include <AL/al.h>
#include <AL/alc.h>
#include <quick_al/device.hpp>

namespace quick3d::al
{
	class Context
	{
	private:
		Device* device;
		ALCcontext* context;

		void setup_context() noexcept(false);
		void destroy_context() noexcept;

	public:
		Context(Device& device) noexcept(false);
		Context(Context&) = delete;
		~Context() noexcept;

		ALCcontext* get_context() noexcept;
	};
}