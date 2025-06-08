#include "Game/Game.h"

int main(int argc, char *argv[]) {
    Game game;
    game.init("ECS v0.0.1", 640, 480);
    game.run();
    return 0;
}