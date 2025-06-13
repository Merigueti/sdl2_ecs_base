#include "ECS/ECSManager.h"
#include "Systems/RenderSystem.h"
#include <cassert>

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

template <typename T, typename... Args>
void ECSManager::addSystem(Args&&... args) {
    static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
    size_t typeHash = typeid(T).hash_code();
    assert(systems.find(typeHash) == systems.end() && "System already added");
    systems[typeHash] = std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
std::shared_ptr<T> ECSManager::getSystem() {
    size_t typeHash = typeid(T).hash_code();
    auto it = systems.find(typeHash);
    if (it != systems.end()) {
        return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
}

void ECSManager::update(float deltaTime) {
    for (auto& [type, system] : systems) {
        system->update(deltaTime);
    }
}

template void ECSManager::addSystem<RenderSystem, SDL_Renderer*>(SDL_Renderer*&&);
template std::shared_ptr<RenderSystem> ECSManager::getSystem<RenderSystem>();