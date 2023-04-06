#include "timer.hpp"

ni::utils::TimeRecorder::TimeRecorder()
	: lastUpdate(Clock::now())
{
}

void ni::utils::TimeRecorder::update()
{
	lastUpdate = Clock::now();
}

ni::utils::Seconds ni::utils::TimeRecorder::getSpanAsSeconds()
{
	return std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - lastUpdate);
}

ni::utils::MilliSeconds ni::utils::TimeRecorder::getSpanAsMilliSeconds()
{
	return std::chrono::duration_cast<MilliSeconds>(Clock::now() - lastUpdate);
}

ni::utils::MicroSeconds ni::utils::TimeRecorder::getSpanAsMicroSeconds()
{
	return std::chrono::duration_cast<MicroSeconds>(Clock::now() - lastUpdate);
}

ni::utils::NanoSeconds ni::utils::TimeRecorder::getSpanAsNanoSeconds()
{
	return std::chrono::duration_cast<NanoSeconds>(Clock::now() - lastUpdate);
}

ni::utils::Timer::Timer(const MilliSeconds& i, std::function<void(void)> callback)
	: interval(i), shoudPause(false), shouldQuit(nullptr)
{
}

ni::utils::Timer::Timer()
	: interval(MilliSeconds(0)), shoudPause(false), shouldQuit(nullptr)
{
}

ni::utils::Timer::~Timer()
{
	*shouldQuit = true;
}

void ni::utils::Timer::setInterval(const MicroSeconds& i)
{
	interval = i;
}

const ni::utils::MicroSeconds& ni::utils::Timer::getInterval()
{
	return interval;
}

void ni::utils::Timer::joinRun(const std::function<void(void)>& func)
{
	callback = func;
	std::thread([&]()
		{
			bool subthreadShoudQuit;
			shouldQuit = &subthreadShoudQuit;

			while (!subthreadShoudQuit)
			{
				while (shoudPause)
					std::this_thread::sleep_for(MicroSeconds(1));

				if (recorder.getSpanAsMicroSeconds() < interval)
					std::this_thread::sleep_for(MicroSeconds(1));
				else
				{
					callback();
					recorder.update();
				}
			}
		}).detach();
}

void ni::utils::Timer::detachRun(const std::function<void(void)>& func)
{
	callback = func;
	std::thread([&]()
		{
			bool subthreadShoudQuit{ false };
			shouldQuit = &subthreadShoudQuit;

			while (!subthreadShoudQuit)
			{
				while (shoudPause)
					std::this_thread::sleep_for(MicroSeconds(1));

				if (recorder.getSpanAsMicroSeconds() < interval)
					std::this_thread::sleep_for(MicroSeconds(1));
				else
				{
					callback();
					recorder.update();
				}
			}
		}).detach();
}

void ni::utils::Timer::pause()
{
	shoudPause = true;
}

void ni::utils::Timer::resume()
{
	shoudPause = false;
}
