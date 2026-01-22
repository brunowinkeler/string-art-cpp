#ifndef APP_ALGORITHM_NAILCIRCLE_HPP
#define APP_ALGORITHM_NAILCIRCLE_HPP

#include "app/model/Nail.hpp"
#include <vector>

namespace app::algorithm
{
    class NailCircle
    {
    public:
        NailCircle() = default;

        void Generate(int centerX, int centerY, int radius, int numNails);
        const model::Nail& GetNail(int index) const;
        int GetCount() const;
        const std::vector<model::Nail>& GetNails() const;
        int GetCenterX() const;
        int GetCenterY() const;
        int GetRadius() const;

    private:
        std::vector<model::Nail> m_Nails;
        int m_CenterX = 0;
        int m_CenterY = 0;
        int m_Radius = 0;
    };

} // namespace app::algorithm

#endif // APP_ALGORITHM_NAILCIRCLE_HPP
