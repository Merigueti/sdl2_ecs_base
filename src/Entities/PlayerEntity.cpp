#include "Entities/PlayerEntity.h"
#include "Components/TransformComponent.h"
#include "Systems/RenderSystem.h"

std::shared_ptr<Entity> createPlayer(ECSManager& ecs) {
    auto player = ecs.createEntity();

    auto transform = std::make_shared<TransformComponent>(100, 300, 32, 32);
    player->addComponent<TransformComponent>(transform);

    auto renderSystem = ecs.getSystem<RenderSystem>();
    if (renderSystem) {
        renderSystem->addEntity(player);
    }

    return player;
}
