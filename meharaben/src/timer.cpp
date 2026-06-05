#include "../include/timer.h"
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <iostream>

double waitForReaction(double timeoutSeconds) {
    using clock = std::chrono::steady_clock;
    auto start = clock::now();

    // Flush any leftover input
    while (_kbhit()) _getch();

    while (true) {
        auto now = clock::now();
        double elapsed = std::chrono::duration<double>(now - start).count();

        if (elapsed >= timeoutSeconds) {
            return -1.0;  // timeout
        }

        if (_kbhit()) {
            int ch = _getch();
            // Accept ENTER (13) or SPACE (32)
            if (ch == 13 || ch == 32) {
                return elapsed;
            }
        }

        // Small sleep to avoid burning CPU
        Sleep(10);
    }
}
