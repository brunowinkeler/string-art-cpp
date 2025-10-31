#include "LoggerConfig.hpp"
#include <iostream>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>

namespace utils
{
    void LoggerConfig::initialize(const std::string& log_file)
    {
        try
        {
            // Console sink
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

            // File sink
            auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file, true);

            // Combine sinks
            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
            auto logger = std::make_shared<spdlog::logger>("String Art Logger", sinks.begin(), sinks.end());

            spdlog::set_default_logger(logger);
            spdlog::set_level(spdlog::level::info);
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

            spdlog::info("Logger initialized successfully");
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        }
    }

    void LoggerConfig::shutdown()
    {
        spdlog::shutdown();
    }

} // namespace utils
