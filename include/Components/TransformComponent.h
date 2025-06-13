#pragma once
#include "ECS/Component.h"
#include <SDL3/SDL.h>

struct TransformComponent : public Component {
    SDL_FRect rect;
    
    TransformComponent(float x, float y, float w, float h) {
        rect = {x, y, w, h};
    }
};