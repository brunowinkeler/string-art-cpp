#include "ConfigsReader.hpp"
#include "utils/LoggerConfig.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace io
{
    ConfigsReader::ConfigsReader(const std::string& filePath)
    {
        (void)scanConfigsFile(filePath);
    }

    bool ConfigsReader::scanConfigsFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            utils::logger::error("Failed to open config file: {}", filePath.c_str());
            return false;
        }

        try
        {
            nlohmann::json jsonConfig = nlohmann::json::parse(file);
            file.close();

            m_configs.windowTitle = jsonConfig["windowTitle"].get<std::string>();
            m_configs.windowWidth = jsonConfig["windowWidth"].get<int>();
            m_configs.windowHeight = jsonConfig["windowHeight"].get<int>();
            m_configs.numLinesToDraw = jsonConfig["numLinesToDraw"].get<int>();
            m_configs.numNails = jsonConfig["numNails"].get<int>();
            m_configs.inputImagePath = jsonConfig["inputImagePath"].get<std::string>();

            utils::logger::info("Configurations loaded successfully from: {}", filePath.c_str());
            return true;
        }
        catch (const nlohmann::json::exception& e)
        {
            utils::logger::error("Error parsing config file: {}", e.what());
            return false;
        }
    }

    const model::Configs& ConfigsReader::getConfigs() const
    {
        return m_configs;
    }

} // namespace io
