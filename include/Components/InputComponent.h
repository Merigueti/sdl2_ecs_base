#pragma once
#include "ECS/Component.h"

struct InputComponent : public Component {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool action = false;
    InputComponent() = default;
};
