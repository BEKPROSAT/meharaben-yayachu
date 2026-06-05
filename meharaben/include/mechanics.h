#pragma once
#include "structs.h"
#include "players.h"

struct RoundResult {
    bool playerNoticed;   // did selected player react in time?
    bool runnerCaught;    // if chase happened, was runner caught?
    double reactionTime;  // seconds taken to react (-1 = timeout)
    int selectedIndex;    // which seat was tapped
};

// Runner walks and picks a target. Returns seat index chosen.
// If mode is CPU, picks randomly. If HUMAN, prompts runner player.
int walkPhase(const CircleManager& cm, RunnerMode mode);

// Selected player gets a timed reaction window.
// Returns populated RoundResult (reactionTime, playerNoticed).
RoundResult reactPhase(const CircleManager& cm, int selectedIndex);

// Probabilistic chase: returns true if runner was caught.
// Weighted by reactionTime from reactPhase.
bool chasePhase(double reactionTime);

// Punishment mini-game: runner must type a word within time limit.
// Returns true when complete (always eventually passes).
void punishmentPhase(const std::string& runnerName);
