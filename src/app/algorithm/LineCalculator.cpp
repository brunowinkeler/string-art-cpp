#include "LineCalculator.hpp"
#include <algorithm>
#include <cmath>

namespace app::algorithm
{
    std::vector<std::pair<int, int>> LineCalculator::GetLinePixels(int x1, int y1, int x2, int y2)
    {
        std::vector<std::pair<int, int>> pixels;

        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        int x = x1;
        int y = y1;

        pixels.reserve(std::max(dx, dy) + 1);

        while (true)
        {
            pixels.emplace_back(x, y);

            if (x == x2 && y == y2)
                break;

            int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                x += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                y += sy;
            }
        }

        return pixels;
    }

    double LineCalculator::GetDistance(int x1, int y1, int x2, int y2)
    {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }

} // namespace app::algorithm
