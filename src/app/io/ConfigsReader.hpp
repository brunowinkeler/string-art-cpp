#ifndef IO_CONFIGSREADER_HPP
#define IO_CONFIGSREADER_HPP

#include "app/model/Configs.hpp"
#include <string>

namespace app
{
    namespace io
    {
        class ConfigsReader
        {
        public:
            explicit ConfigsReader(const std::string& filePath = "configs.json");
            bool ScanConfigsFile(const std::string& filePath);
            const model::Configs& GetConfigs() const;
            void SetConfigs(const model::Configs& configs);
            void SaveConfigsToFile(const std::string& filePath);

        private:
            model::Configs m_configs;
        };
    }
}

#endif // IO_CONFIGSREADER_HPP
