#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

namespace Resources
{
    struct FontResource
    {
        std::string name;
        std::string path;
    };

    struct ImageResource
    {
        std::string name;
        std::string path;
    };

    namespace Fonts
    {
        inline constexpr FontResource DEFAULT = { "Default", "resources/fonts/Arial.ttf" };
        inline constexpr FontResource TITLE = { "Title", "resources/fonts/Arial-Bold.ttf" };
        inline constexpr FontResource MONO = { "Mono", "resources/fonts/Courier.ttf" };
    }

    namespace Images
    {
        inline constexpr ImageResource LOGO = { "Logo", "resources/images/logo.png" };
        inline constexpr ImageResource BACKGROUND = { "Background", "resources/images/background.png" };
        inline constexpr ImageResource ICON = { "Icon", "resources/images/icon.png" };
    }
}

#endif
