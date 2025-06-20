#include "ECS/Entity.h"

Entity::Entity(int id) : id(id) {}

Entity::~Entity() {
    components.clear();
}

int Entity::getId() const {
    return id;
}