#ifndef MODEL_CONFIGS_HPP
#define MODEL_CONFIGS_HPP

#include <string>

namespace model
{
    struct Configs
    {
        std::string windowTitle;
        int windowWidth;
        int windowHeight;
        int numLinesToDraw;
        int numNails;
        std::string inputImagePath;
    };
} // namespace model

#endif // MODEL_CONFIGS_HPP
