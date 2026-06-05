#pragma once
#include "structs.h"
#include <vector>

void displayCircle(const std::vector<Player>& players, int runnerIndex);
void displayBanner();
void displayScoreboard(const std::vector<Player>& players);
void clearScreen();
void pauseMs(int ms);
void printChant();
