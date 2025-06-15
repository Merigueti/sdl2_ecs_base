#pragma once
#include "ECS/System.h"
#include <SDL3/SDL.h>
#include <memory>

class MovementSystem : public System {
public:
    MovementSystem() = default;
    void update(float deltaTime) override;
};
