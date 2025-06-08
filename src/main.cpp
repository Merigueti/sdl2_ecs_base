#include <SDL2/SDL.h>
#include <iostream>
#include <cstdio> // Para snprintf

// Constantes
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// FPS desejado
const int TARGET_FPS = 60;
const float TARGET_FRAME_TIME = 1.0f / TARGET_FPS;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "ECS v0.0.1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Erro ao criar renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // Controle de tempo
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float deltaTime = 0;

    // Controle de FPS
    int frameCount = 0;
    float fpsTimer = 0.0f;
    char title[100];

    while (running)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (float)((now - last) / (double)SDL_GetPerformanceFrequency());

        // Atualiza contador de FPS
        frameCount++;
        fpsTimer += deltaTime;
        if (fpsTimer >= 1.0f)
        {
            float fps = frameCount / fpsTimer;
            snprintf(title, sizeof(title), "ECS v0.0.1 - FPS: %.2f", fps);
            SDL_SetWindowTitle(window, title);
            frameCount = 0;
            fpsTimer = 0.0f;
        }

        // Processa eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Atualiza lógica com deltaTime
        // Ex: posição += velocidade * deltaTime;

        // Renderiza
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Aqui você pode desenhar com base no deltaTime

        SDL_RenderPresent(renderer);

        // FPS cap
        float frameTime = (float)((SDL_GetPerformanceCounter() - now) / (double)SDL_GetPerformanceFrequency());
        if (frameTime < TARGET_FRAME_TIME)
        {
            SDL_Delay((Uint32)((TARGET_FRAME_TIME - frameTime) * 1000.0f));
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
