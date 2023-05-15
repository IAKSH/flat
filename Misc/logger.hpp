#pragma once

#include "disable_copy.hpp"
#include "spdlog/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <string>

namespace flat::misc
{
    class Logger : public DisableCopy
    {
    private:
        std::shared_ptr<spdlog::logger> logger;
        
    public:
        Logger(std::string_view name);
        ~Logger();

        const std::shared_ptr<spdlog::logger>& operator->();
    };

    extern Logger main_logger;
}