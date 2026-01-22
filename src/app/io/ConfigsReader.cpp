#include "ConfigsReader.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace app::io
{
    ConfigsReader::ConfigsReader(const std::string& filePath)
    {
        ScanConfigsFile(filePath);
    }

    bool ConfigsReader::ScanConfigsFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            core::utils::Logger::warn("Config file not found: {}, using defaults", filePath);
            return false;
        }

        try
        {
            nlohmann::json j = nlohmann::json::parse(file);
            file.close();

            if (j.contains("windowTitle"))
                m_configs.windowTitle = j["windowTitle"];
            if (j.contains("windowWidth"))
                m_configs.windowWidth = j["windowWidth"];
            if (j.contains("windowHeight"))
                m_configs.windowHeight = j["windowHeight"];
            if (j.contains("numNails"))
                m_configs.numNails = j["numNails"];
            if (j.contains("numLinesToDraw"))
                m_configs.numLinesToDraw = j["numLinesToDraw"];
            if (j.contains("linesPerFrame"))
                m_configs.linesPerFrame = j["linesPerFrame"];
            if (j.contains("darkenAmount"))
                m_configs.darkenAmount = j["darkenAmount"];
            if (j.contains("minNailDistance"))
                m_configs.minNailDistance = j["minNailDistance"];
            if (j.contains("inputImagePath"))
                m_configs.inputImagePath = j["inputImagePath"];

            core::utils::Logger::info("Config loaded from: {}", filePath);
            return true;
        }
        catch (const nlohmann::json::exception& e)
        {
            core::utils::Logger::error("Error parsing config: {}", e.what());
            return false;
        }
    }

    const model::Configs& ConfigsReader::GetConfigs() const
    {
        return m_configs;
    }

    void ConfigsReader::SaveConfigsToFile(const std::string& filePath)
    {
        nlohmann::json j;
        j["windowTitle"] = m_configs.windowTitle;
        j["windowWidth"] = m_configs.windowWidth;
        j["windowHeight"] = m_configs.windowHeight;
        j["numNails"] = m_configs.numNails;
        j["numLinesToDraw"] = m_configs.numLinesToDraw;
        j["linesPerFrame"] = m_configs.linesPerFrame;
        j["darkenAmount"] = m_configs.darkenAmount;
        j["minNailDistance"] = m_configs.minNailDistance;
        j["inputImagePath"] = m_configs.inputImagePath;

        std::ofstream file(filePath);
        if (!file.is_open())
        {
            core::utils::Logger::error("Failed to save config to: {}", filePath);
            return;
        }

        file << j.dump(4);
        file.close();

        core::utils::Logger::info("Config saved to: {}", filePath);
    }
} // namespace app::io
