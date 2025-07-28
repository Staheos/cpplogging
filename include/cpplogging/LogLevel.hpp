#ifndef WSTL_LOGGING_LOGLEVEL
#define WSTL_LOGGING_LOGLEVEL


#include <string>
#include "Colors.hpp"


namespace wstl
{
    namespace log
    {
        /// @brief The log levels that are used to filter log messages.
        enum class LogLevel : int
        {
            trace = 1,
            debug = 2,
            info = 4,
            warning = 8,
            error = 32,
            fatal = 128,

            ok = 16,
            supreme = 64,
        };

        Color LogLevelColor(LogLevel logLevel);

        template <typename T>
        std::basic_string<T> LogLevelString(LogLevel logLevel);
    }
}

template <typename T>
std::basic_string<T> wstl::log::LogLevelString(LogLevel logLevel)
{
    switch (logLevel)
    {
    case LogLevel::fatal:
        return "FATAL";
    case LogLevel::error:
        return "ERROR";
    case LogLevel::warning:
        return "WARNING";
    case LogLevel::info:
        return "INFO";
    case LogLevel::debug:
        return "DEBUG";
    case LogLevel::trace:
        return "TRACE";
    case LogLevel::ok:
        return "OK";
    case LogLevel::supreme:
        return "SUPREME";
    default:
        return "VERBOSE";
    }
}

#endif // WSTL_LOGGING_LOGLEVEL