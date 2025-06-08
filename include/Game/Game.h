#pragma once
#include <SDL2/SDL.h>
#include <string>

class ECSManager; // Forward declaration

class Game {
public:
    Game();
    ~Game();
    
    void init(const std::string& title, int width, int height);
    void run();
    
private:
    void processInput();
    void update(float deltaTime);
    void render();
    void updateFPS(float deltaTime);
    void capFrameRate(Uint64 frameStart) const;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    ECSManager* ecsManager;
    
    // FPS control
    int frameCount;
    float fpsTimer;
    std::string baseTitle;
    int targetFPS;
    float targetFrameTime;
};