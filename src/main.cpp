#include "app/Application.hpp"
#include "utils/LoggerConfig.hpp"

int main()
{
    utils::LoggerConfig::initialize("logs/log.txt");

    utils::logger::info("Application started.");

    app::Application application;
    application.run();

    utils::LoggerConfig::shutdown();

    return 0;
}
