#pragma once

#include "../core/template.hpp"
#include <chrono>
#include <thread>
#include <functional>

namespace ni::utils
{
	using Seconds = std::chrono::seconds;
	using MilliSeconds = std::chrono::milliseconds;
	using MicroSeconds = std::chrono::microseconds;
	using NanoSeconds = std::chrono::nanoseconds;
	using Clock = std::chrono::steady_clock;

	class TimeRecorder
	{
	private:
		Clock::time_point lastUpdate;

	public:
		TimeRecorder();
		~TimeRecorder() = default;
		void update();
		Seconds getSpanAsSeconds();
		MilliSeconds getSpanAsMilliSeconds();
		MicroSeconds getSpanAsMicroSeconds();
		NanoSeconds getSpanAsNanoSeconds();
	};

	class Timer : public core::DisableCopy
	{
	private:
		bool shoudPause;
		bool* shouldQuit;
		std::function<void(void)> callback;
		TimeRecorder recorder;
		MicroSeconds interval;

	public:
		Timer(const MilliSeconds& i, std::function<void(void)> callback);
		Timer();
		~Timer();
		void setInterval(const MicroSeconds& i);
		const MicroSeconds& getInterval();
		void joinRun(const std::function<void(void)>& func);
		void detachRun(const std::function<void(void)>& func);
		void pause();
		void resume();
	};
}