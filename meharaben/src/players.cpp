#include "../include/players.h"
#include <stdexcept>
#include <cstdlib>

void CircleManager::setup(const std::vector<std::string>& names, int firstRunnerIdx) {
    circle.clear();
    for (const auto& name : names) {
        circle.push_back(Player(name));
    }
    // Pull the runner out of the circle
    runnerName = circle[firstRunnerIdx].name;
    circle[firstRunnerIdx].score++;   // count this as a runner turn
    runnerIndex = firstRunnerIdx;
    circle.erase(circle.begin() + firstRunnerIdx);
    // After erase, runnerIndex is now the seat that "faces" where runner was
    if (runnerIndex >= (int)circle.size()) runnerIndex = 0;
}

int CircleManager::randomTarget() const {
    if (circle.empty()) return 0;
    return rand() % (int)circle.size();
}

void CircleManager::swapRunner(int seatIndex) {
    if (seatIndex < 0 || seatIndex >= (int)circle.size()) return;

    std::string oldRunnerName = runnerName;

    // New runner is the player being displaced
    runnerName = circle[seatIndex].name;
    circle[seatIndex].score++;

    // Insert the old runner into that seat
    circle[seatIndex] = Player(oldRunnerName);

    // runnerIndex for display purposes = seatIndex
    runnerIndex = seatIndex;
}
