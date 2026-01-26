#include "StringArtGenerator.hpp"
#include "core/utils/LoggerConfig.hpp"
#include <algorithm>
#include <limits>

namespace app::algorithm
{
    void StringArtGenerator::Initialize(SDL_Surface* sourceSurface, int numNails, int maxLines,
        int darkenAmount, int minNailDistance)
    {
        if (!sourceSurface)
        {
            core::utils::Logger::error("StringArtGenerator: Cannot initialize with null surface");
            return;
        }

        SDL_Surface* copy = SDL_ConvertSurface(sourceSurface, sourceSurface->format);
        if (!copy)
        {
            core::utils::Logger::error("StringArtGenerator: Failed to create working surface copy");
            return;
        }
        m_WorkingSurface.reset(copy);

        int centerX = sourceSurface->w / 2;
        int centerY = sourceSurface->h / 2;
        int radius = std::min(sourceSurface->w, sourceSurface->h) / 2 - 5;

        m_NailCircle.Generate(centerX, centerY, radius, numNails);

        m_State.Reset();
        m_State.maxLines = maxLines;
        m_State.minNailDistance = minNailDistance;
        m_State.currentNailIndex = 0;
        m_State.path.push_back(0);

        m_DarkenAmount = darkenAmount;
        m_Initialized = true;

        core::utils::Logger::info("StringArtGenerator: {} nails, {} lines, darken={}, minDist={}",
            numNails, maxLines, darkenAmount, minNailDistance);
    }

    bool StringArtGenerator::Step()
    {
        if (!m_Initialized || m_State.isComplete)
        {
            return false;
        }

        // Find the best nail to connect to
        int bestNail = FindBestNail();

        if (bestNail < 0)
        {
            m_State.isComplete = true;
            core::utils::Logger::info("StringArtGenerator: No valid nail found, simulation complete");
            return false;
        }

        // Get the line pixels
        const auto& fromNail = m_NailCircle.GetNail(m_State.currentNailIndex);
        const auto& toNail = m_NailCircle.GetNail(bestNail);
        auto linePixels = LineCalculator::GetLinePixels(fromNail.m_x, fromNail.m_y, toNail.m_x, toNail.m_y);

        // Darken those pixels in the working surface
        core::imaging::ImageModifier::DarkenLine(m_WorkingSurface.get(), linePixels, m_DarkenAmount);

        // Update state
        m_State.totalThreadLength += LineCalculator::GetDistance(fromNail.m_x, fromNail.m_y, toNail.m_x, toNail.m_y);
        m_State.currentNailIndex = bestNail;
        m_State.path.push_back(bestNail);
        m_State.linesDrawn++;

        // Check if we've reached the maximum
        if (m_State.linesDrawn >= m_State.maxLines)
        {
            m_State.isComplete = true;
            core::utils::Logger::info("StringArtGenerator: Reached {} lines, simulation complete", m_State.linesDrawn);
        }

        return true;
    }

    void StringArtGenerator::RunComplete()
    {
        if (!m_Initialized)
        {
            core::utils::Logger::error("StringArtGenerator: Cannot run - not initialized");
            return;
        }

        m_State.isRunning = true;

        while (!m_State.isComplete)
        {
            Step();

            // Log progress every 100 lines
            if (m_State.linesDrawn % 100 == 0)
            {
                core::utils::Logger::info("StringArtGenerator: Progress {}/{} lines",
                    m_State.linesDrawn, m_State.maxLines);
            }
        }

        m_State.isRunning = false;
        core::utils::Logger::info("StringArtGenerator: Complete! {} lines, {:.1f} pixels of thread",
            m_State.linesDrawn, m_State.totalThreadLength);
    }

    void StringArtGenerator::Reset()
    {
        m_State.Reset();
        m_WorkingSurface.reset();
        m_Initialized = false;
    }

    int StringArtGenerator::FindBestNail()
    {
        int bestNail = -1;
        int bestScore = std::numeric_limits<int>::min();
        int numNails = m_NailCircle.GetCount();
        int validNailsChecked = 0;

        for (int i = 0; i < numNails; ++i)
        {
            if (i == m_State.currentNailIndex)
                continue;

            int distance = std::abs(i - m_State.currentNailIndex);
            distance = std::min(distance, numNails - distance);
            if (distance < m_State.minNailDistance)
                continue;

            validNailsChecked++;
            int score = CalculateLineScore(m_State.currentNailIndex, i);

            if (score > bestScore)
            {
                bestScore = score;
                bestNail = i;
            }
        }

        if (m_State.linesDrawn < 5)
        {
            core::utils::Logger::info("FindBestNail: checked {} valid nails, best={} score={}",
                validNailsChecked, bestNail, bestScore);
        }

        return bestNail;
    }

    int StringArtGenerator::CalculateLineScore(int fromNail, int toNail)
    {
        const auto& from = m_NailCircle.GetNail(fromNail);
        const auto& to = m_NailCircle.GetNail(toNail);

        auto linePixels = LineCalculator::GetLinePixels(from.m_x, from.m_y, to.m_x, to.m_y);

        int score = 0;
        for (const auto& [x, y] : linePixels)
        {
            int brightness = core::imaging::ImageAnalyzer::GetPixelBrightness(m_WorkingSurface.get(), x, y);
            // Lower brightness = darker pixel = higher score
            score += (255 - brightness);
        }

        return score;
    }

} // namespace app::algorithm
