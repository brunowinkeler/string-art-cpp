#ifndef UTILS_LOGGERCONFIG_HPP
#define UTILS_LOGGERCONFIG_HPP

#include <spdlog/spdlog.h>
#include <string>

namespace core
{
    namespace utils
    {
        namespace Logger = spdlog;

        class LoggerConfig
        {
        public:
            static void Initialize(const std::string& logger_name, const std::string& log_file = "log.txt");
            static void Shutdown();
        };
    }
}

#endif // UTILS_LOGGERCONFIG_HPP
