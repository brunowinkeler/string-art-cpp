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
        inline constexpr FontResource DEFAULT = { "Default", "resources/fonts/Arial.ttf" };
        inline constexpr FontResource TITLE = { "Title", "resources/fonts/Arial-Bold.ttf" };
        inline constexpr FontResource MONO = { "Mono", "resources/fonts/Courier.ttf" };
    }

    namespace Images
    {
        inline constexpr ImageResource SCREW1 = { "Screw1", "resources/images/screw1.png" };
        inline constexpr ImageResource SCREW2 = { "Screw2", "resources/images/screw2.png" };
    }
}

#endif
