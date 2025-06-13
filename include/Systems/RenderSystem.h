#pragma once
#include "ECS/System.h"
#include <SDL3/SDL.h>
#include <memory>

class RenderSystem : public System {
public:
    explicit RenderSystem(SDL_Renderer* renderer);
    void update(float deltaTime) override;
    void render();
    
private:
    SDL_Renderer* renderer;
};
