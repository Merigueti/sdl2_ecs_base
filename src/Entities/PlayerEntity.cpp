#include "Entities/PlayerEntity.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"

std::shared_ptr<Entity> createPlayer(ECSManager& ecs) {
    auto player = ecs.createEntity();

    auto transform = std::make_shared<TransformComponent>(100.0f, 300.0f, 32.0f, 32.0f);
    auto velocity = std::make_shared<VelocityComponent>(0.0f, 0.0f);

    player->addComponent<TransformComponent>(transform);
    player->addComponent<VelocityComponent>(velocity);

    auto renderSystem = ecs.getSystem<RenderSystem>();
    if (renderSystem) {
        renderSystem->addEntity(player);
    }

    auto movementSyste = ecs.getSystem<MovementSystem>();
    if(movementSyste) {
        movementSyste->addEntity(player);
    }

    return player;
}
