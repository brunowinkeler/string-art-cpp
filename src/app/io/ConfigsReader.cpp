#include "ConfigsReader.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace app
{
    namespace io
    {
        ConfigsReader::ConfigsReader(const std::string& filePath)
        {
            (void)ScanConfigsFile(filePath);
        }

        bool ConfigsReader::ScanConfigsFile(const std::string& filePath)
        {
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                core::utils::Logger::error("Failed to open config file: {}", filePath.c_str());
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

                core::utils::Logger::info("Configurations loaded successfully from: {}", filePath.c_str());
                return true;
            }
            catch (const nlohmann::json::exception& e)
            {
                core::utils::Logger::error("Error parsing config file: {}", e.what());
                return false;
            }
        }

        const model::Configs& ConfigsReader::GetConfigs() const
        {
            return m_configs;
        }

        void ConfigsReader::SaveConfigsToFile(const std::string& filePath)
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
                core::utils::Logger::error("Failed to open config file for writing: {}", filePath.c_str());
                return;
            }

            file << jsonConfig.dump(4); // Pretty print with 4 spaces indentation
            file.close();

            core::utils::Logger::info("Configurations saved successfully to: {}", filePath.c_str());
        }
    }
}
