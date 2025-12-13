#include "app/Application.hpp"
#include "core/utils/LoggerConfig.hpp"

int main()
{
    core::utils::LoggerConfig::Initialize("logs/log.txt");

    core::utils::Logger::info("Application started.");

    app::Application application;
    application.Run();

    core::utils::LoggerConfig::Shutdown();

    return 0;
}
