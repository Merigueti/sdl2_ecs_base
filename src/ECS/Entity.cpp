#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"

Entity::Entity(int id) : id(id) {}

Entity::~Entity() {
    components.clear();
}

template <typename T>
void Entity::addComponent(std::shared_ptr<T> component) {
    for (auto& comp : components) {
        if (std::dynamic_pointer_cast<T>(comp)) {
            return;
        }
    }
    components.push_back(component);
}

template <typename T>
std::shared_ptr<T> Entity::getComponent() {
    for (auto& comp : components) {
        if (auto derived = std::dynamic_pointer_cast<T>(comp)) {
            return derived;
        }
    }
    return nullptr;
}

int Entity::getId() const {
    return id;
}

template void Entity::addComponent<TransformComponent>(std::shared_ptr<TransformComponent>);
template std::shared_ptr<TransformComponent> Entity::getComponent<TransformComponent>();

template void Entity::addComponent<>(std::shared_ptr<VelocityComponent>);
template std::shared_ptr<VelocityComponent> Entity::getComponent<VelocityComponent>();