#pragma once
#include "structs.h"
#include <vector>
#include <string>

class CircleManager {
public:
    std::vector<Player> circle;  // seated players only
    int runnerIndex;             // index in circle of who JUST left (used for display)
    std::string runnerName;      // name of the current runner (outside the circle)

    CircleManager() : runnerIndex(0) {}

    // Populate circle from a name list, pick first runner by index
    void setup(const std::vector<std::string>& names, int firstRunnerIdx);

    // Return a random seated player index (not the runner's old seat)
    int randomTarget() const;

    // Swap: runner takes seatIndex, that player becomes new runner
    void swapRunner(int seatIndex);

    // Number of seated players
    int size() const { return (int)circle.size(); }
};
