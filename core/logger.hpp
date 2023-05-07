#pragma once

#include "template.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <string>

namespace ni::core
{
    class Logger : public DisableCopy
    {
    private:
        std::string logrName;
        std::shared_ptr<spdlog::logger> logger;
        void initialize();

    public:
        Logger(std::string_view name);
        ~Logger() = default;
        const std::shared_ptr<spdlog::logger>& operator->() {return logger;}
    };
}