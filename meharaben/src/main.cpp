#include "../include/game.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand((unsigned int)time(nullptr));

    Game game;
    game.setup();
    game.run();

    return 0;
}
