#include "Game/MainScene.h"
#include "Entities/PlayerEntity.h"
#include "Components/TransformComponent.h"
#include "Systems/RenderSystem.h"

void MainScene::load(ECSManager& ecs) {
    for (int i = 0; i < 5; i ++){
        createPlayer(ecs);
    }
}

void MainScene::update(float deltaTime) {
}
