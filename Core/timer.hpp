#pragma once

#include "../../Misc/disable_copy.hpp"
#include "../../Misc/ctti.hpp"
#include <functional>
#include <chrono>
#include <thread>

namespace flat
{
    using Seconds = std::chrono::seconds;
	using MilliSeconds = std::chrono::milliseconds;
	using MicroSeconds = std::chrono::microseconds;
	using NanoSeconds = std::chrono::nanoseconds;
	using Clock = std::chrono::steady_clock;

    class TimeRecorder
    {
    private:
        Clock::time_point last_update;

    public:
        TimeRecorder()
            : last_update(Clock::now())
        {}

        ~TimeRecorder() = default;

        void update()
        {
            last_update = Clock::now();
        }
        
        auto get_time_span_sec()
        {
            return std::chrono::duration_cast<Seconds>(Clock::now() - last_update);
        }

        auto get_time_span_ms()
        {
            return std::chrono::duration_cast<MilliSeconds>(Clock::now() - last_update);
        }

        auto get_time_span_us()
        {
            return std::chrono::duration_cast<MicroSeconds>(Clock::now() - last_update);
        }

        auto get_time_span_ns()
        {
            return std::chrono::duration_cast<NanoSeconds>(Clock::now() - last_update);
        }
    };

    template <typename T>
    concept TimeUnitType = misc::any_same<T,Seconds,MilliSeconds,MicroSeconds,NanoSeconds>();

    using CallbackFunc = std::function<void()>;

    template <TimeUnitType T>
    class Timer : misc::DisableCopy
    {
    private:
        bool should_pause;
        bool* should_quit;
        CallbackFunc callback;
        TimeRecorder recorder;
        T interval;

    public:
        Timer(const T& i)
            : interval(i), should_pause(false), should_quit(nullptr)
        {}

        Timer()
            : interval(0),should_pause(false),should_quit(nullptr)
        {}

        ~Timer()
        {
            *should_quit = true;
        }

        void set_interval(const T& i)
        {
            interval = i;
        }

        const T& get_interval()
        {
            return interval;
        }

        void join_run(CallbackFunc func)
        {
            callback = func;
            std::thread([this](){
                bool this_thread_should_quit {false};
                should_quit = &this_thread_should_quit;

                while(!this_thread_should_quit)
                {
                    while(should_pause || recorder.get_time_span_ns() < interval)
                        std::this_thread::sleep_for(NanoSeconds(1));

                    callback();
                    recorder.update();
                }
            }).join();
        }

        void detach_run(CallbackFunc func)
        {
            callback = func;
            std::thread([this](){
                bool this_thread_should_quit {false};
                should_quit = &this_thread_should_quit;

                while(!this_thread_should_quit)
                {
                    while(should_pause || recorder.get_time_span_ns() < interval)
                        std::this_thread::sleep_for(NanoSeconds(1));

                    callback();
                    recorder.update();
                }
            }).detach();
        }

        void pause()
        {
            should_pause = true;
        }

        void resume()
        {
            should_pause = false;
        }
    };
}