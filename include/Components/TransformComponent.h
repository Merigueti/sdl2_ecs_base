#pragma once
#include "ECS/Component.h"
#include <SDL3/SDL.h>

struct TransformComponent : public Component {
    SDL_FPoint position;
    SDL_FPoint scale;
    float rotation;
    SDL_FPoint size;
    
    TransformComponent(float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f, float rot = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f)
        : position{x, y}, scale{scaleX, scaleY}, rotation{rot}, size{w, h} {}

    SDL_FRect GetRect() const {
        return SDL_FRect{ position.x, position.y, size.x * scale.x, size.y * scale.y };
    }
};
