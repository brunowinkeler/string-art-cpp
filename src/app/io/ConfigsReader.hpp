#ifndef IO_CONFIGSREADER_HPP
#define IO_CONFIGSREADER_HPP

#include "app/model/Configs.hpp"
#include <string>

namespace app::io
{
    class ConfigsReader
    {
    public:
        explicit ConfigsReader(const std::string& filePath = "configurations/default_configs.json");
        bool ScanConfigsFile(const std::string& filePath);
        const model::Configs& GetConfigs() const;
        void SaveConfigsToFile(const std::string& filePath);

    private:
        model::Configs m_configs;
    };
} // namespace app::io

#endif // IO_CONFIGSREADER_HPP
