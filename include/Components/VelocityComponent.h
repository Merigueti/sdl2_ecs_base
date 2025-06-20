#pragma once
#include "ECS/Component.h"
#include <SDL3/SDL.h>

struct VelocityComponent : public Component {
    SDL_FPoint velocity;
    
    VelocityComponent(float vx = 0.0f, float vy = 0.0f)
        : velocity{vx, vy} {}
};
