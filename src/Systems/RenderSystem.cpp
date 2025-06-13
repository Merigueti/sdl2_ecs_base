#include "Systems/RenderSystem.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include <iostream>

RenderSystem::RenderSystem(SDL_Renderer* renderer)
    : renderer(renderer) {}

void RenderSystem::update(float deltaTime) {
    //render();
}

void RenderSystem::render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    for (auto& entity : entities) {
        auto transform = entity->getComponent<TransformComponent>();
        std::cout << 'a' << std::endl;
        if (!transform) continue;
        std::cout << 'b' << std::endl;
        SDL_FRect dstRect = {
            transform->rect.x,
            transform->rect.y,
            transform->rect.w,
            transform->rect.h
        };

        SDL_RenderFillRect(renderer, &dstRect);
    }
}