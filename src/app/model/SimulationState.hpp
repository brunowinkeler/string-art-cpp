#ifndef APP_MODEL_SIMULATIONSTATE_HPP
#define APP_MODEL_SIMULATIONSTATE_HPP

#include <vector>

namespace app::model
{
    struct SimulationState
    {
        bool isRunning = false;
        bool isComplete = false;
        int currentNailIndex = 0;
        int linesDrawn = 0;
        int maxLines = 3000;
        std::vector<int> path;
        double totalThreadLength = 0.0;
        int minNailDistance = 20;

        void Reset()
        {
            isRunning = false;
            isComplete = false;
            currentNailIndex = 0;
            linesDrawn = 0;
            totalThreadLength = 0.0;
            path.clear();
        }
    };

} // namespace app::model

#endif // APP_MODEL_SIMULATIONSTATE_HPP
