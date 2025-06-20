#include "ECS/Entity.h"
#include "Systems/MovementSystem.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include <iostream>


void MovementSystem::update(float deltaTime)
{
    for (auto& entity : entities) {
        auto transform = entity->getComponent<TransformComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();
        if (transform && velocity) {
            transform->position.x += velocity->velocity.x * deltaTime;
            transform->position.y += velocity->velocity.y * deltaTime;
        }
    }
}
