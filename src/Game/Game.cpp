#include "Game/Game.h"
#include "ECS/ECSManager.h"
#include <iostream>
#include <cstdio>

Game::Game() : window(nullptr, SDL_DestroyWindow),
               renderer(nullptr, SDL_DestroyRenderer),
               ecsManager(),
               isRunning(false), frameCount(0), fpsTimer(0.0f),
               targetFPS(60), targetFrameTime(1.0f / 60)
{
    //pass
}

Game::~Game()
{
    SDL_Quit();
}

void Game::init(const std::string &title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    window.reset(SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN));

    if (!window.get())
    {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        return;
    }

    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!renderer.get())
    {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        window.reset();
        return;
    }

    ecsManager = std::make_unique<ECSManager>();
    baseTitle = title;
    isRunning = true;
}

void Game::run()
{
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float deltaTime = 0;

    while (isRunning)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (float)((now - last) / (double)SDL_GetPerformanceFrequency());

        updateFPS(deltaTime);
        processInput();
        update(deltaTime);
        render();
        capFrameRate(now);
    }
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }
}

void Game::update(float deltaTime)
{
    ecsManager->update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    // ecsManager->render(renderer);

    SDL_RenderPresent(renderer.get());
}

void Game::updateFPS(float deltaTime)
{
    frameCount++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0f)
    {
        float fps = frameCount / fpsTimer;
        char titleBuffer[100];
        snprintf(titleBuffer, sizeof(titleBuffer), "%s - FPS: %.2f", baseTitle.c_str(), fps);
        SDL_SetWindowTitle(window.get(), titleBuffer);
        frameCount = 0;
        fpsTimer = 0.0f;
    }
}

void Game::capFrameRate(Uint64 frameStart) const
{
    float frameTime = (float)((SDL_GetPerformanceCounter() - frameStart) / (double)SDL_GetPerformanceFrequency());
    if (frameTime < targetFrameTime)
    {
        SDL_Delay((Uint32)((targetFrameTime - frameTime) * 1000.0f));
    }
}