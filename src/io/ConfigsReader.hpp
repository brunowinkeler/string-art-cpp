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

    private:
        model::Configs m_configs;
    };
} // namespace io

#endif // IO_CONFIGSREADER_HPP
