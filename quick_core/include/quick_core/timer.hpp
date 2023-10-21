#pragma once

#include <chrono>

namespace quick3d::ecs
{
	template <typename T>
	class Timer
	{
	private:
		std::chrono::time_point<T> recorded_time_point;

	public:
		Timer() noexcept
		{
			record_time_point();
		}

		~Timer() = default;
		
		template <typename U>
		U get_timer_duration() noexcept
		{
			return std::chrono::duration_cast<U>(T::now() - recorded_time_point);
		}

		void record_time_point() noexcept
		{
			recorded_time_point = T::now();
		}
	};

	using SystemTimer = Timer<std::chrono::system_clock>;
	using SteadyTimer = Timer<std::chrono::steady_clock>;
	using HightResTimer = Timer<std::chrono::high_resolution_clock>;
}