#ifndef MODEL_CONFIGS_HPP
#define MODEL_CONFIGS_HPP

#include <string>

namespace app
{
    namespace model
    {
        struct Configs
        {
            std::string windowTitle = "String Art Application";
            int windowWidth = 1280;
            int windowHeight = 720;
            int numLinesToDraw = 1000;
            int numNails = 360;
            std::string inputImagePath = "input/image.jpg";
        };
    } // namespace model
} // namespace app

#endif // MODEL_CONFIGS_HPP
