#pragma once

#include <chrono>
#include <thread>
#include <functional>

namespace flat::utils
{
	using Seconds = std::chrono::seconds;
	using MilliSeconds = std::chrono::milliseconds;
	using MicroSeconds = std::chrono::microseconds;
	using NanoSeconds = std::chrono::nanoseconds;
	using Clock = std::chrono::steady_clock;

	class TimeRecorder
	{
	private:
		std::chrono::steady_clock::time_point lastUpdate;

	public:
		TimeRecorder();
		~TimeRecorder() = default;
		void update();
		Seconds getSpanAsSeconds();
		MilliSeconds getSpanAsMilliSeconds();
		MicroSeconds getSpanAsMicroSeconds();
		NanoSeconds getSpanAsNanoSeconds();
	};

	class Timer
	{
	private:
		bool shoudPause;
		bool* shouldQuit;
		TimeRecorder recorder;
		MicroSeconds interval;
		std::thread thread;
		std::function<void(void)> callbackFunc;
		void makeupThread();

	public:
		Timer(const MilliSeconds& i, std::function<void(void)> callback);
		Timer();
		~Timer();
		void setInterval(const MicroSeconds& i);
		const MicroSeconds& getInterval();
		void setCallback(std::function<void(void)> callback);
		void join();
		void detach();
		void pause();
		void resume();
	};
}