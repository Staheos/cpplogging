#ifndef WSTL_LOGGING_LOGGER
#define WSTL_LOGGING_LOGGER

#define COMPILATION_LOG_LEVEL wstl::log::LogLevel::debug

#include <iostream>
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <fstream>

#include "Colors.hpp"
#include "LogLevel.hpp"

#include <fmt/core.h>


#define DATE() \
    []() { \
		std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now(); \
		int64_t timestamp = now.time_since_epoch().count(); \
		std::time_t currentTime = std::chrono::system_clock::to_time_t(now); \
		tm utcTime; \
		gmtime_s(&utcTime, &currentTime); \
		std::stringstream ss_date; \
		ss_date << std::put_time(&utcTime, "%Y-%m-%d_%H:%M:%S") << ':' << std::setfill('0') << std::setw(3) << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000; \
		return ss_date.str(); }()

namespace wstl
{
    namespace log
    {

        class Logger
        {
            std::queue<std::string> _queue;
            std::mutex _mutex;
            std::condition_variable _cv;
            std::atomic<bool> _running;
            std::thread _workerThread;
            std::string _filename = "log.txt";

        private:
            /// Constructor shall be private in singletons, initialize the worker thread and open the default log file.
            Logger() : _running(true)
            {
                // Launch the worker thread
                _workerThread = std::thread(&Logger::workerLoop, this);
            }

        public:
            static void log(const std::string &message, const wstl::log::LogLevel logLevel = wstl::log::LogLevel::info)
            {
                Logger::instance().Log(wstl::log::color_string(message, wstl::log::LogLevelColor(logLevel)));
            }

            template <typename... Args>
            static void logf(const std::string &format, wstl::log::LogLevel logLevel, Args... args)
            {
                Logger::log(fmt::format(format, args...), logLevel);
            }

            template <wstl::log::LogLevel logLevel, typename... Args>
            constexpr static void logfl(const std::string &format, Args... args)
            {
                if constexpr (COMPILATION_LOG_LEVEL <= logLevel)
                {
                    Logger::logf("[" + DATE() + "] " + format, logLevel, args...);
                }
            }

            /*template <typename ...Args>
            static void logFatal(const std::string format, Args ...args)
            {
                Logger::logf(format, wstl::log::LogLevel::fatal, args...);
            }

            template <typename ...Args>
            static void logError(const std::string format, Args ...args)
            {
                Logger::logf(format, wstl::log::LogLevel::error, args...);
            }

            template <typename ...Args>
            static void logWarning(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::warning, args...);
            }

            template <typename ...Args>
            static void logInfo(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::info, args...);
            }

            template <typename ...Args>
            static void logDebug(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::debug, args...);
            }

            template <typename ...Args>
            static void logTrace(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::trace, args...);
            }

            template <typename ...Args>
            static void logOk(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::ok, args...);
            }

            template <typename ...Args>
            static void logImportant(const std::string format, Args ...args)
            {
                logger::logf(format, wstl::log::LogLevel::important, args...);
            }*/

            // Singleton access if desired, or just create an instance somewhere
            static Logger &instance()
            {
                static Logger instance;
                return instance;
            }

            // Public interface for log
            void Log(const std::string &message)
            {
                {
                    std::lock_guard<std::mutex> lock(_mutex);
                    _queue.push(message);
                }
                _cv.notify_one();
            }

            // Optional: Provide some thread-safe mechanism to set output file, etc.
            void setOutputFile(const std::string &filename)
            {
                std::lock_guard<std::mutex> lock(_mutex);
                _filename = filename;
            }

            // Make sure to properly stop the worker thread when shutting down
            void stop()
            {
                bool expected = true;
                if (_running.compare_exchange_strong(expected, false))
                {
                    // If we successfully changed it from true to false
                    _cv.notify_one(); // Wake up the worker thread
                    if (_workerThread.joinable())
                    {
                        _workerThread.join();
                    }
                }
            }

        private:
            ~Logger()
            {
                // Safely stop worker thread
                stop();
            }

        public:
            /// Not copyable
            Logger(const Logger &) = delete;

            /// Not assignable
            Logger &operator=(const Logger &) = delete;

        private:
            /// Worker thread loop to handle IO operations on console or files
            void workerLoop()
            {
                std::ofstream _outputStream; // Log file handle
                _outputStream = std::ofstream(_filename, std::ios::app);

                // // Close the current file if open
                // if (_outputStream.is_open()) {
                //     _outputStream.close();
                // }
                // _outputStream.open(filename, std::ios::app);

                while (_running)
                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _cv.wait(lock, [this]
                             {
                // Wake up if new data is available or if we are shutting down
                return !_queue.empty() || !_running; });

                    // Process queue
                    while (!_queue.empty())
                    {
                        const std::string &msg = _queue.front();
                        std::cout << msg << '\n';
                        _outputStream << msg << std::endl;
                        _queue.pop();
                    }
                }

                // Flush anything remaining after _running becomes false
                while (!_queue.empty())
                {
                    const auto &msg = _queue.front();
                    std::cout << msg << std::endl;
                    _outputStream << msg << std::endl;
                    _queue.pop();
                }

                _outputStream.flush();
                _outputStream.close();
            }
        };

    }
}

#endif // !WSTL_LOGGING_LOGGER
