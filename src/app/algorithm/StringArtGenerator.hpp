#ifndef APP_ALGORITHM_STRINGARTGENERATOR_HPP
#define APP_ALGORITHM_STRINGARTGENERATOR_HPP

#include "LineCalculator.hpp"
#include "NailCircle.hpp"
#include "app/model/SimulationState.hpp"
#include "core/imaging/ImageAnalyzer.hpp"
#include "core/imaging/ImageModifier.hpp"
#include <SDL3/SDL.h>
#include <memory>

namespace app::algorithm
{
    class StringArtGenerator
    {
    public:
        StringArtGenerator() = default;

        void Initialize(SDL_Surface* sourceSurface, int numNails, int maxLines);
        bool Step();
        void RunComplete();
        void Reset();

        const model::SimulationState& GetState() const
        {
            return m_State;
        }

        const NailCircle& GetNailCircle() const
        {
            return m_NailCircle;
        }

        SDL_Surface* GetWorkingSurface() const
        {
            return m_WorkingSurface.get();
        }

        bool IsInitialized() const
        {
            return m_Initialized;
        }

    private:
        int FindBestNail();
        int CalculateLineScore(int fromNail, int toNail);

    private:
        NailCircle m_NailCircle;
        model::SimulationState m_State;
        std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_WorkingSurface{ nullptr, SDL_DestroySurface };
        bool m_Initialized = false;
        int m_DarkenAmount = 25;
    };

} // namespace app::algorithm

#endif // APP_ALGORITHM_STRINGARTGENERATOR_HPP
