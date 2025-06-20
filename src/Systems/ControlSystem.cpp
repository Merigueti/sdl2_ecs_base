#include <SDL3/SDL.h>
#include <iostream>
#include "Systems/ControlSystem.h"
#include "ECS/Entity.h"
#include "Components/InputComponent.h"

void ControlSystem::handleEvent(const SDL_Event &event)
{
    for (auto &entity : entities)
    {
        auto input = entity->getComponent<InputComponent>();
        if (!input)
            continue;

        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP)
        {
            const SDL_Keycode key = event.key.key;
            const bool pressed = (event.type == SDL_EVENT_KEY_DOWN);

            switch (key)
            {
            case SDLK_W:
                input->up = pressed;
                break;
            case SDLK_S:
                input->down = pressed;
                break;
            case SDLK_A:
                input->left = pressed;
                break;
            case SDLK_D:
                input->right = pressed;
                break;
            case SDLK_SPACE:
                input->action = pressed;
                break;
            default:
                break;
            }
        }
    }
}

void ControlSystem::update(float deltaTime)
{
    (void)deltaTime;
}
