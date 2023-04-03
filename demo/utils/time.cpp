#include "time.hpp"

#include "log.hpp"

flat::utils::TimeRecorder::TimeRecorder()
	: lastUpdate(Clock::now())
{
}

void flat::utils::TimeRecorder::update()
{
	lastUpdate = Clock::now();
}

flat::utils::Seconds flat::utils::TimeRecorder::getSpanAsSeconds()
{
	return std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - lastUpdate);
}

flat::utils::MilliSeconds flat::utils::TimeRecorder::getSpanAsMilliSeconds()
{
	return std::chrono::duration_cast<MilliSeconds>(Clock::now() - lastUpdate);
}

flat::utils::MicroSeconds flat::utils::TimeRecorder::getSpanAsMicroSeconds()
{
	return std::chrono::duration_cast<MicroSeconds>(Clock::now() - lastUpdate);
}

flat::utils::NanoSeconds flat::utils::TimeRecorder::getSpanAsNanoSeconds()
{
	return std::chrono::duration_cast<NanoSeconds>(Clock::now() - lastUpdate);
}

flat::utils::Timer::Timer(const MilliSeconds& i, std::function<void(void)> callback)
	: interval(i), shoudPause(false), shouldQuit(nullptr)
{
}

flat::utils::Timer::Timer()
	: interval(MilliSeconds(0)), shoudPause(false), shouldQuit(nullptr)
{
}

flat::utils::Timer::~Timer()
{
	*shouldQuit = true;
}

void flat::utils::Timer::setInterval(const MicroSeconds& i)
{
	interval = i;
}

const flat::utils::MicroSeconds& flat::utils::Timer::getInterval()
{
	return interval;
}

void flat::utils::Timer::joinRun(const std::function<void(void)>& func)
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

void flat::utils::Timer::detachRun(const std::function<void(void)>& func)
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

void flat::utils::Timer::pause()
{
	shoudPause = true;
}

void flat::utils::Timer::resume()
{
	shoudPause = false;
}
