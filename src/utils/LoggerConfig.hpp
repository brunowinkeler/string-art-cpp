#ifndef UTILS_LOGGERCONFIG_HPP
#define UTILS_LOGGERCONFIG_HPP

#include <spdlog/spdlog.h>
#include <string>

namespace utils
{
    namespace logger = spdlog;

    class LoggerConfig
    {
    public:
        static void initialize(const std::string& log_file = "log.txt");
        static void shutdown();
    };

}

#endif // UTILS_LOGGERCONFIG_HPP
