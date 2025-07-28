#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "Logger.hpp"


#define LOG_FATAL(...) wstl::log::Logger::logfl<wstl::log::LogLevel::fatal>(__VA_ARGS__);
#define LOG_ERROR(...) wstl::log::Logger::logfl<wstl::log::LogLevel::error>(__VA_ARGS__);
#define LOG_WARNING(...) wstl::log::Logger::logfl<wstl::log::LogLevel::warning>(__VA_ARGS__);
#define LOG_INFO(...) wstl::log::Logger::logfl<wstl::log::LogLevel::info>(__VA_ARGS__);
#define LOG_DEBUG(...) wstl::log::Logger::logfl<wstl::log::LogLevel::debug>(__VA_ARGS__);
#define LOG_TRACE(...) wstl::log::Logger::logfl<wstl::log::LogLevel::trace>(__VA_ARGS__);
#define LOG_OK(...) wstl::log::Logger::logfl<wstl::log::LogLevel::ok>(__VA_ARGS__);
#define LOG_IMPORTANT(...) wstl::log::Logger::logfl<wstl::log::LogLevel::supreme>(__VA_ARGS__);