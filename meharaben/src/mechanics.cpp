#include "../include/mechanics.h"
#include "../include/timer.h"
#include "../include/display.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <chrono>
#include <conio.h>
#include <windows.h>

// ── Walk Phase ──────────────────────────────────────────────────────────────
int walkPhase(const CircleManager& cm, RunnerMode mode) {
    if (mode == RunnerMode::CPU) {
        // CPU runner: random pause then pick a target
        int steps = (rand() % 4) + 1;
        for (int i = 0; i < steps; i++) {
            std::cout << "  " << cm.runnerName << " is walking around the circle...\n";
            pauseMs(700);
        }
        int target = cm.randomTarget();
        std::cout << "\n  * " << cm.runnerName
                  << " secretly taps behind seat " << target
                  << " (" << cm.circle[target].name << ") *\n\n";
        pauseMs(800);
        return target;
    } else {
        // Human runner
        std::cout << "  " << cm.runnerName << ", you are the runner!\n";
        std::cout << "  Walk around and choose a player to tap.\n\n";
        std::cout << "  Seated players:\n";
        for (int i = 0; i < cm.size(); i++) {
            std::cout << "    [" << i << "] " << cm.circle[i].name << "\n";
        }
        std::cout << "\n  Enter seat number to tap (or -1 to keep walking): ";

        int choice = -1;
        while (choice < 0 || choice >= cm.size()) {
            std::cin >> choice;
            if (choice == -1) {
                std::cout << "  Still walking...\n";
                std::cout << "  Enter seat number to tap: ";
                choice = -1;
                continue;
            }
            if (choice < 0 || choice >= cm.size()) {
                std::cout << "  Invalid seat. Try again: ";
                choice = -1;
            }
        }
        std::cout << "\n  You tapped " << cm.circle[choice].name << "!\n\n";
        return choice;
    }
}

// ── React Phase ─────────────────────────────────────────────────────────────
RoundResult reactPhase(const CircleManager& cm, int selectedIndex) {
    RoundResult result;
    result.selectedIndex = selectedIndex;
    result.runnerCaught = false;

    std::string selectedName = cm.circle[selectedIndex].name;

    std::cout << "  " << selectedName
              << ", something was dropped behind you!\n";
    std::cout << "  Press ENTER or SPACE quickly if you notice! (2.5 seconds)\n\n";

    pauseMs(300);

    double t = waitForReaction(2.5);
    result.reactionTime = t;

    if (t < 0) {
        result.playerNoticed = false;
        std::cout << "  " << selectedName << " didn't notice in time!\n";
        std::cout << "  " << cm.runnerName << " sneaks into the seat...\n\n";
        pauseMs(1000);
    } else {
        result.playerNoticed = true;
        std::cout << "  " << selectedName << " noticed! (reaction: "
                  << t << "s)\n";
        std::cout << "  CHASE!\n\n";
        pauseMs(600);
    }
    return result;
}

// ── Chase Phase ──────────────────────────────────────────────────────────────
bool chasePhase(double reactionTime) {
    // Weighted catch probability based on reaction speed
    int catchChance;
    if (reactionTime < 0) {
        catchChance = 0;   // no chase (shouldn't be called)
    } else if (reactionTime < 0.5) {
        catchChance = 70;  // very fast reaction
    } else if (reactionTime < 1.5) {
        catchChance = 40;  // normal reaction
    } else {
        catchChance = 15;  // slow reaction
    }

    std::cout << "  Both are racing around the circle!\n";
    pauseMs(400);
    std::cout << "  .\n"; pauseMs(300);
    std::cout << "  ..\n"; pauseMs(300);
    std::cout << "  ...\n\n"; pauseMs(400);

    int roll = rand() % 100;
    bool caught = (roll < catchChance);
    return caught;
}

// ── Punishment Phase ─────────────────────────────────────────────────────────
void punishmentPhase(const std::string& runnerName) {
    const char* words[] = {"DANCE", "JUMP", "SPIN", "CLAP", "LAUGH"};
    const char* word = words[rand() % 5];

    std::cout << "  " << runnerName << " got caught! Time for a punishment!\n\n";
    pauseMs(500);
    std::cout << "  Type this word in 4 seconds: " << word << "\n";
    std::cout << "  > ";

    // Flush cin
    std::cin.ignore(1000, '\n');

    using clock = std::chrono::steady_clock;
    auto start = clock::now();

    std::string input;
    std::getline(std::cin, input);

    double elapsed = std::chrono::duration<double>(clock::now() - start).count();

    // Convert input to uppercase for comparison
    for (auto& c : input) c = toupper(c);

    if (elapsed <= 4.0 && input == std::string(word)) {
        std::cout << "\n  Well done! Punishment complete.\n\n";
    } else if (elapsed > 4.0) {
        std::cout << "\n  Too slow! The crowd laughs at " << runnerName << "!\n\n";
    } else {
        std::cout << "\n  Wrong word! The crowd laughs at " << runnerName << "!\n\n";
    }
    pauseMs(1000);
}
