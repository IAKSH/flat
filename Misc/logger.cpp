#include "logger.hpp"
#include <iostream>

namespace flat::misc
{
    Logger main_logger("Flat");
}

flat::misc::Logger::Logger(std::string_view name)
{
    try
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        logger = spdlog::stdout_color_mt(name.data());
        logger->set_level(spdlog::level::trace);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
        std::terminate();
    }
}

flat::misc::Logger::~Logger() = default;

const std::shared_ptr<spdlog::logger>& flat::misc::Logger::operator->()
{
    return logger;
}