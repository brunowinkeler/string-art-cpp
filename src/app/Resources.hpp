#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string_view>

namespace Resources
{
    struct FontResource
    {
        std::string_view name;
        std::string_view path;
    };

    struct ImageResource
    {
        std::string_view name;
        std::string_view path;
    };

    namespace Fonts
    {
        inline constexpr FontResource DEFAULT = { "Default", "assets/fonts/arial.ttf" };
        inline constexpr FontResource TITLE = { "Title", "assets/fonts/arial-bold.ttf" };
        inline constexpr FontResource MONO = { "Mono", "assets/fonts/courier.ttf" };
    }

    namespace Images
    {
        inline constexpr ImageResource SCREW1 = { "Screw1", "assets/images/screw1.png" };
        inline constexpr ImageResource SCREW2 = { "Screw2", "assets/images/screw2.png" };
    }
}

#endif
