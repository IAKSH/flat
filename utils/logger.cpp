#include "logger.hpp"

#include <iostream>

namespace ni::utils
{
    Logger coreLogger("Core");
    Logger flatLogger("Flat");
    Logger otherLogger("Other");
}

ni::utils::Logger::Logger(std::string_view name)
    : logrName{name}
{
    initialize();
}

void ni::utils::Logger::initialize()
{
    try
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        logger = spdlog::stdout_color_mt(logrName);
        logger->set_level(spdlog::level::trace);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
        abort();
    }
}
