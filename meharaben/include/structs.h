#pragma once
#include <string>
#include <vector>

enum class GamePhase {
    WALKING,
    REACTING,
    CHASING,
    PUNISHMENT,
    SWAP,
    GAME_OVER
};

struct Player {
    std::string name;
    int score;          // times as runner (lower = luckier)
    Player(const std::string& n) : name(n), score(0) {}
};

enum class RunnerMode {
    HUMAN,
    CPU
};
