#pragma once

#include "ECS/ECSManager.h"
#include <memory>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void load(ECSManager& ecs) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void unload(ECSManager& ecs) {}
};
