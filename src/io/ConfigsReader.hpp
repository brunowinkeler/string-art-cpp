#ifndef IO_CONFIGSREADER_HPP
#define IO_CONFIGSREADER_HPP

#include "model/Configs.hpp"
#include <string>

namespace io
{
    class ConfigsReader
    {
    public:
        explicit ConfigsReader(const std::string& filePath = "resources/configurations/configs.json");
        bool scanConfigsFile(const std::string& filePath);
        const model::Configs& getConfigs() const;
        void setConfigs(const model::Configs& configs);
        void saveConfigsToFile(const std::string& filePath);

    private:
        model::Configs m_configs;
    };
}

#endif // IO_CONFIGSREADER_HPP
