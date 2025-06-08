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