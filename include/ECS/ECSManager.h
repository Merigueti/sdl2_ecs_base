#pragma once
#include <memory>
#include <unordered_map>
#include <cassert>
#include <stdexcept>
#include "Entity.h"
#include "System.h"

class ECSManager {
public:
    std::shared_ptr<Entity> createEntity();
    void destroyEntity(int entityId);

    template <typename T, typename... Args>
    void addSystem(Args&&... args);

    template <typename T>
    std::shared_ptr<T> getSystem();

    void update(float deltaTime);

private:
    std::unordered_map<int, std::shared_ptr<Entity>> entities;
    std::unordered_map<size_t, std::shared_ptr<System>> systems;
    int nextEntityId = 0;
};

// ----------------------------
// Implementação dos templates
// ----------------------------

template <typename T, typename... Args>
void ECSManager::addSystem(Args&&... args) {
    static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
    size_t typeHash = typeid(T).hash_code();

    if (systems.find(typeHash) != systems.end()) {
        throw std::runtime_error("System already added");
    }

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
