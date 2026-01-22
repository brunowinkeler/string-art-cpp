#ifndef APP_ALGORITHM_LINECALCULATOR_HPP
#define APP_ALGORITHM_LINECALCULATOR_HPP

#include <utility>
#include <vector>

namespace app::algorithm
{
    class LineCalculator
    {
    public:
        static std::vector<std::pair<int, int>> GetLinePixels(int x1, int y1, int x2, int y2);
        static double GetDistance(int x1, int y1, int x2, int y2);
    };

} // namespace app::algorithm

#endif // APP_ALGORITHM_LINECALCULATOR_HPP
