#include "Game/Game.h"
#include "Game/Scene.h"
#include "Game/MainScene.h"
#include "ECS/ECSManager.h"
#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"
#include <iostream>
#include <cstdio>

Game::Game() : window(nullptr, SDL_DestroyWindow),
               renderer(nullptr, SDL_DestroyRenderer),
               ecsManager(),
               isRunning(false), frameCount(0), fpsTimer(0.0f),
               targetFPS(60), targetFrameTime(1.0f / 60)
{
    // pass
}

Game::~Game()
{
    SDL_Quit();
}

void Game::init(const std::string &title, int width, int height)
{

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                    "Falha ao inicializar SDL_VIDEO: %s",
                    SDL_GetError());
        return;
    }


    window.reset(SDL_CreateWindow(title.c_str(), width, height, 0));

    if (!window.get())
    {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        return;
    }

    renderer.reset(SDL_CreateRenderer(window.get(), nullptr));
    if (!renderer.get())
    {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        window.reset();
        return;
    }

    ecsManager = std::make_unique<ECSManager>();
    ecsManager->addSystem<RenderSystem>(renderer.get());
    ecsManager->addSystem<MovementSystem>();

    currentScene = std::make_unique<MainScene>();
    currentScene->load(*ecsManager);

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
        if (event.type == SDL_EVENT_QUIT)
        {
            isRunning = false;
        }
    }
}

void Game::update(float deltaTime)
{
    if (currentScene) {
        currentScene->update(deltaTime);
    }
    ecsManager->update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());

    auto renderSystem = ecsManager->getSystem<RenderSystem>();
    renderSystem->render();

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
    Uint64 frameEnd = SDL_GetPerformanceCounter();
    Uint64 elapsedTicks = frameEnd - frameStart;
    Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 elapsedNs = (elapsedTicks * 1000000000ull) / freq;
    Uint64 nsPerFrame = static_cast<Uint64>(targetFrameTime * 1e9f);

    if (elapsedNs < nsPerFrame) {
        SDL_DelayNS(nsPerFrame - elapsedNs);
    }
}
