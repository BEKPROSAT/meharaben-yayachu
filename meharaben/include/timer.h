#pragma once

// Returns how many seconds the player took to press ENTER.
// Returns -1.0 if they didn't respond within timeoutSeconds.
// Uses _kbhit() + conio.h (Windows only, works with MinGW).
double waitForReaction(double timeoutSeconds);
