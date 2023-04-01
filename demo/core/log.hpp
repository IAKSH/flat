#pragma once

#include <memory>
#include <string_view>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace flat::core
{
	class Log
	{
	private:
		inline static std::shared_ptr<spdlog::logger> logger;

	public:
		Log() = delete;
		~Log() = delete;

		static void init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");
			logger = spdlog::stdout_color_mt("CORE");
			logger->set_level(spdlog::level::trace);
		}

		static std::shared_ptr<spdlog::logger>& getLogger() { return logger; }
	};

#define LOG_TRACE(...)         ::flat::core::Log::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::flat::core::Log::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::flat::core::Log::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::flat::core::Log::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::flat::core::Log::getLogger()->critical(__VA_ARGS__)
}
