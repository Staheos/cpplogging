#include "cpplogging/LogLevel.hpp"


wstl::log::Color wstl::log::LogLevelColor(LogLevel logLevel)
{
    switch (logLevel)
    {
    case LogLevel::fatal:
        return Color::FG_RED;
    case LogLevel::error:
        return Color::FG_BRIGHT_RED;
    case LogLevel::warning:
        return Color::FG_YELLOW;
    case LogLevel::info:
        return Color::RESET;
    case LogLevel::debug:
        return Color::DIM;
    case LogLevel::trace:
        return Color::FG_MAGENTA;
    case LogLevel::ok:
        return Color::FG_GREEN;
    case LogLevel::supreme:
        return Color::FG_BRIGHT_CYAN;
    default:
        return Color::FG_DEFAULT;
    }
}
