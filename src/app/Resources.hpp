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
        inline constexpr ImageResource NAIL1 = { "Nail1", "assets/images/nail1.png" };
        inline constexpr ImageResource NAIL2 = { "Nail2", "assets/images/nail2.png" };
        inline constexpr ImageResource NAIL3 = { "Nail3", "assets/images/nail3.png" };
        inline constexpr ImageResource WOMAN = { "Woman", "assets/images/woman.png" };
    }
}

#endif
