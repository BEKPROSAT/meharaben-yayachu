#include "../include/game.h"
#include "../include/display.h"
#include "../include/mechanics.h"
#include <iostream>
#include <limits>

// ── Setup ────────────────────────────────────────────────────────────────────
void Game::setup() {
    displayBanner();

    // Choose runner mode
    std::cout << "  Runner mode:\n";
    std::cout << "    [1] Human runner  (hot-seat, one PC)\n";
    std::cout << "    [2] CPU runner    (AI picks automatically)\n";
    std::cout << "  Choice: ";
    int modeChoice;
    std::cin >> modeChoice;
    mode = (modeChoice == 1) ? RunnerMode::HUMAN : RunnerMode::CPU;

    // Get player count
    int n = 0;
    while (n < 5 || n > 15) {
        std::cout << "\n  How many players? (5-15): ";
        std::cin >> n;
        if (n < 5 || n > 15)
            std::cout << "  Must be between 5 and 15.\n";
    }

    // Get names
    std::vector<std::string> names;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n  Enter player names:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "    Player " << (i + 1) << ": ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) name = "Player" + std::to_string(i + 1);
        names.push_back(name);
    }

    // Pick first runner
    int firstRunner = rand() % n;
    std::cout << "\n  Randomly selected first runner: " << names[firstRunner] << "\n";
    pauseMs(1200);

    cm.setup(names, firstRunner);
    running = true;
    roundCount = 0;
}

// ── Main Game Loop ────────────────────────────────────────────────────────────
void Game::run() {
    while (running) {
        doRound();
        roundCount++;

        if (roundCount % 3 == 0) {
            // Show scoreboard every 3 rounds
            // We need all players including runner for scoreboard
            // Build a combined list
            std::vector<Player> all = cm.circle;
            all.push_back(Player(cm.runnerName));
            displayScoreboard(all);
        }

        if (!askContinue()) {
            running = false;
        }
    }

    // Final scoreboard
    std::cout << "\n  Game over after " << roundCount << " rounds!\n";
    std::vector<Player> all = cm.circle;
    Player runnerP(cm.runnerName);
    all.push_back(runnerP);
    displayScoreboard(all);
    std::cout << "  Thanks for playing Meharaben Yayachu!\n\n";
}

// ── Single Round ──────────────────────────────────────────────────────────────
void Game::doRound() {
    clearScreen();
    std::cout << "  === Round " << (roundCount + 1) << " ===\n";
    std::cout << "  Runner: " << cm.runnerName << "\n";

    displayCircle(cm.circle, cm.runnerIndex);
    printChant();
    pauseMs(1200);

    // Walk phase — loop until a target is picked
    // (human can delay; CPU always picks after a few steps)
    int target = walkPhase(cm, mode);

    // React phase
    RoundResult result = reactPhase(cm, target);

    if (result.playerNoticed) {
        // Chase phase
        bool caught = chasePhase(result.reactionTime);
        if (caught) {
            std::cout << "  " << cm.runnerName << " was CAUGHT by "
                      << cm.circle[target].name << "!\n\n";
            pauseMs(800);
            punishmentPhase(cm.runnerName);
            // Runner stays as runner (no swap)
        } else {
            std::cout << "  " << cm.runnerName << " made it to the seat!\n";
            std::cout << "  " << cm.circle[target].name << " is the new runner!\n\n";
            pauseMs(1000);
            cm.swapRunner(target);
        }
    } else {
        // Runner takes seat silently
        std::cout << "  " << cm.runnerName << " takes seat " << target << ".\n";
        std::cout << "  " << cm.circle[target].name << " is the new runner!\n\n";
        pauseMs(1000);
        cm.swapRunner(target);
    }
}

// ── Continue Prompt ───────────────────────────────────────────────────────────
bool Game::askContinue() {
    std::cout << "  Continue playing? (y/n): ";
    char ch;
    std::cin >> ch;
    return (ch == 'y' || ch == 'Y');
}
