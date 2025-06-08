#pragma once
#include <SDL2/SDL.h>
#include "ECS/ECSManager.h"

class Game {
public:
    Game();
    ~Game();
    
    void init(const char* title, int width, int height);
    void run();
    
private:
    void processInput();
    void update(float deltaTime);
    void render();
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    ECSManager ecsManager;
};