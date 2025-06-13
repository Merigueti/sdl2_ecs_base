#pragma once
#include <memory>
#include <unordered_map>
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