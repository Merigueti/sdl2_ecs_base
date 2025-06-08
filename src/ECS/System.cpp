#include "ECS/System.h"

void System::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

void System::removeEntity(int entityId) {
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [entityId](const std::shared_ptr<Entity>& e) {
                return e->getId() == entityId;
            }),
        entities.end()
    );
}