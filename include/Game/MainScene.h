#pragma once

#include "Scene.h"

class MainScene : public Scene {
public:
    void load(ECSManager& ecs) override;
    void update(float deltaTime) override;
};
