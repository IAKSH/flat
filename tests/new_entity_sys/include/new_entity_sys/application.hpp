#pragma once

#include <quick_gl/context.hpp>

namespace quick3d::test
{
	class Application
	{
	private:
		gl::Context context;
		float delta_ms;

		void initialize() noexcept;
		void record_delta_time() noexcept;
		void do_tick() noexcept;

	public:
		Application(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept;
		Application(Application&) = delete;
		~Application() = default;

		void run() noexcept;
	};
}