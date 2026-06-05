#include "../include/display.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

void clearScreen() {
    system("cls");
}

void pauseMs(int ms) {
    Sleep(ms);
}

void printChant() {
    std::cout << "\n";
    std::cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "   Meharaben Yayachu!  Meharaben Yayachu!\n";
    std::cout << "  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void displayBanner() {
    clearScreen();
    std::cout << "==============================================\n";
    std::cout << "         MEHARABEN YAYACHU\n";
    std::cout << "   Traditional Ethiopian Circle Game\n";
    std::cout << "==============================================\n\n";
}

void displayCircle(const std::vector<Player>& players, int runnerIndex) {
    int n = (int)players.size();
    if (n == 0) return;

    std::cout << "\n  [ SEATED PLAYERS ]\n\n";

    int topCount = (n + 1) / 2;

    // Top row
    std::cout << "    ";
    for (int i = 0; i < topCount; i++) {
        std::cout << "[" << std::setw(2) << i << ":" << std::left << std::setw(8) << players[i].name << "] ";
    }
    std::cout << "\n";

    std::cout << "\n";

    // Bottom row (reverse order)
    if (n - topCount > 0) {
        std::cout << "    ";
        for (int i = n - 1; i >= topCount; i--) {
            std::cout << "[" << std::setw(2) << i << ":" << std::left << std::setw(8) << players[i].name << "] ";
        }
        std::cout << "\n";
    }

    std::cout << "\n  >> RUNNER (outside): " << players[runnerIndex < n ? runnerIndex : 0].name << "\n\n";
}

void displayScoreboard(const std::vector<Player>& players) {
    std::cout << "\n  ======= SCOREBOARD =======\n";
    for (const auto& p : players) {
        std::cout << "  " << std::left << std::setw(14) << p.name
                  << " was runner x" << p.score << "\n";
    }
    std::cout << "  ==========================\n\n";
}
