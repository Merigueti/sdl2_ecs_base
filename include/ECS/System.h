#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class System {
public:
    virtual ~System() = default;
    virtual void update(float deltaTime) = 0;
    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(int entityId);
    
protected:
    std::vector<std::shared_ptr<Entity>> entities;
};