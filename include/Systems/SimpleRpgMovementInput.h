#pragma once
#include "ECS/System.h"
#include <SDL3/SDL.h>
#include <memory>

class SimpleRpgMovementInput : public System {
public:
    SimpleRpgMovementInput() = default;
    void update(float deltaTime) override;
};
