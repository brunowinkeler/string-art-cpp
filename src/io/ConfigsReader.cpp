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

    void ConfigsReader::saveConfigsToFile(const std::string& filePath)
    {
        nlohmann::json jsonConfig;
        jsonConfig["windowTitle"] = m_configs.windowTitle;
        jsonConfig["windowWidth"] = m_configs.windowWidth;
        jsonConfig["windowHeight"] = m_configs.windowHeight;
        jsonConfig["numLinesToDraw"] = m_configs.numLinesToDraw;
        jsonConfig["numNails"] = m_configs.numNails;
        jsonConfig["inputImagePath"] = m_configs.inputImagePath;

        std::ofstream file(filePath);
        if (!file.is_open())
        {
            utils::logger::error("Failed to open config file for writing: {}", filePath.c_str());
            return;
        }

        file << jsonConfig.dump(4); // Pretty print with 4 spaces indentation
        file.close();

        utils::logger::info("Configurations saved successfully to: {}", filePath.c_str());
    }
}
