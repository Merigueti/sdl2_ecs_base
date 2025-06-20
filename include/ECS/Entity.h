#pragma once
#include <vector>
#include <memory>
#include "Component.h"

class Entity {
public:
    Entity(int id);
    ~Entity();
    
    template <typename T>
    void addComponent(std::shared_ptr<T> component);
    
    template <typename T>
    std::shared_ptr<T> getComponent();
    
    int getId() const;
    
private:
    int id;
    std::vector<std::shared_ptr<Component>> components;
};


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