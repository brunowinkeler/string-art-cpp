#include "NailCircle.hpp"
#include <cmath>

namespace app::algorithm
{
    void NailCircle::Generate(int centerX, int centerY, int radius, int numNails)
    {
        m_CenterX = centerX;
        m_CenterY = centerY;
        m_Radius = radius;
        m_Nails.clear();
        m_Nails.reserve(numNails);

        for (int i = 0; i < numNails; ++i)
        {
            double angle = (2.0 * M_PI * i) / numNails;
            model::Nail nail;
            nail.m_x = static_cast<int>(centerX + radius * std::cos(angle));
            nail.m_y = static_cast<int>(centerY + radius * std::sin(angle));
            m_Nails.push_back(nail);
        }
    }

    const model::Nail& NailCircle::GetNail(int index) const
    {
        return m_Nails[index];
    }

    int NailCircle::GetCount() const
    {
        return static_cast<int>(m_Nails.size());
    }

    const std::vector<model::Nail>& NailCircle::GetNails() const
    {
        return m_Nails;
    }

    int NailCircle::GetCenterX() const
    {
        return m_CenterX;
    }

    int NailCircle::GetCenterY() const
    {
        return m_CenterY;
    }

    int NailCircle::GetRadius() const
    {
        return m_Radius;
    }

} // namespace app::algorithm
