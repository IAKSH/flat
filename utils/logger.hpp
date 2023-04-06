#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ni::utils
{
    class Logger
    {
    private:
        std::string logrName;
        std::shared_ptr<spdlog::logger> logger;
        void initialize();

    public:
        Logger(std::string_view name);
        ~Logger() = default;

        const std::shared_ptr<spdlog::logger>& operator()()
        {
            return logger;
        }
    };

    extern Logger coreLogger;
    extern Logger flatLogger;
    extern Logger otherLogger;
}