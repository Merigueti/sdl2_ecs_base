#include "ECS/ECSManager.h"

std::shared_ptr<Entity> ECSManager::createEntity() {
    auto entity = std::make_shared<Entity>(nextEntityId++);
    entities[entity->getId()] = entity;
    return entity;
}

void ECSManager::destroyEntity(int entityId) {
    entities.erase(entityId);

    for (auto& [type, system] : systems) {
        system->removeEntity(entityId);
    }
}

void ECSManager::update(float deltaTime) {
    for (auto& [type, system] : systems) {
        system->update(deltaTime);
    }
}
