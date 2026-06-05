#pragma once
#include "structs.h"
#include "players.h"
#include <vector>
#include <string>

class Game {
public:
    CircleManager cm;
    RunnerMode mode;
    bool running;
    int roundCount;

    Game() : mode(RunnerMode::CPU), running(false), roundCount(0) {}

    // Collect player names, choose mode, pick first runner
    void setup();

    // Main game loop
    void run();

private:
    void doRound();
    bool askContinue();
};
