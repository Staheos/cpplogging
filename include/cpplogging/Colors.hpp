#ifndef WSTL_LOGGING_COLORS
#define WSTL_LOGGING_COLORS

#include <string>

namespace wstl
{
    namespace log
    {
        enum class Color : int
        {
            RESET = 0,
            BOLD = 1,
            DIM = 2,
            ITALIC = 3,
            UNDERLINED = 4,
            BLINK = 5,

            FG_BLACK = 30,
            FG_RED = 31,
            FG_GREEN = 32,
            FG_YELLOW = 33,
            FG_BLUE = 34,
            FG_MAGENTA = 35,
            FG_CYAN = 36,
            FG_WHITE = 37,
            FG_DEFAULT = 39,

            BG_BLACK = 40,
            BG_RED = 41,
            BG_GREEN = 42,
            BG_YELLOW = 43,
            BG_BLUE = 44,
            BG_MAGENTA = 45,
            BG_CYAN = 46,
            BG_WHITE = 47,
            BG_DEFAULT = 49,

            FG_BRIGHT_BLACK = 90,
            FG_BRIGHT_RED = 91,
            FG_BRIGHT_GREEN = 92,
            FG_BRIGHT_YELLOW = 93,
            FG_BRIGHT_BLUE = 94,
            FG_BRIGHT_MAGENTA = 95,
            FG_BRIGHT_CYAN = 96,
            FG_BRIGHT_WHITE = 97,

            BG_BRIGHT_BLACK = 100,
            BG_BRIGHT_RED = 101,
            BG_BRIGHT_GREEN = 102,
            BG_BRIGHT_YELLOW = 103,
            BG_BRIGHT_BLUE = 104,
            BG_BRIGHT_MAGENTA = 105,
            BG_BRIGHT_CYAN = 106,
            BG_BRIGHT_WHITE = 107
        };

        template <typename T>
        std::basic_string<T> color_sequence(Color color);

        template <typename T>
        std::basic_string<T> color_string(const std::basic_string<T> str, Color color);
    }
}

template <typename T>
std::basic_string<T> wstl::log::color_sequence(wstl::log::Color color)
{
    return "\x1B[" + std::to_string(static_cast<int>(color)) + "m";
}

template <typename T>
std::basic_string<T> wstl::log::color_string(const std::basic_string<T> str, wstl::log::Color color)
{
    return wstl::log::color_sequence<T>(color) + str + wstl::log::color_sequence<T>(wstl::log::Color::RESET);
}

#endif // WSTL_LOGGING_COLORS