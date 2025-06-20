#pragma once
#include "ECS/System.h"
#include <SDL3/SDL.h>
#include <memory>

class ControlSystem : public System {
public:
    ControlSystem() = default;
    void handleEvent(const SDL_Event& event);
    void update(float deltaTime) override;
};
