#pragma once
#include "ECS/Component.h"

struct MouseComponent : public Component {
    bool left = false;
    bool middle = false;
    bool right = false;
    float scrollX = 0.0f;
    float scrollY = 0.0f;
    float x = 0.0f, y = 0.0f;
    MouseComponent() = default;
};
