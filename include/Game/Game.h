#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <memory>

class ECSManager;

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
    
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    std::unique_ptr<ECSManager> ecsManager;

    bool isRunning;
    int frameCount;
    float fpsTimer;
    std::string baseTitle;
    int targetFPS;
    float targetFrameTime;
};