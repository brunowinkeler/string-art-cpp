#ifndef MODEL_CONFIGS_HPP
#define MODEL_CONFIGS_HPP

#include <string>

namespace app::model
{
    struct Configs
    {
        std::string windowTitle = "String Art Application";
        int windowWidth = 1280;
        int windowHeight = 720;
        int numNails = 200;
        int numLinesToDraw = 2000;
        int linesPerFrame = 5;
        int darkenAmount = 25;
        int minNailDistance = 20;
        std::string inputImagePath = "assets/images/woman.png";
    };
} // namespace app::model

#endif // MODEL_CONFIGS_HPP
