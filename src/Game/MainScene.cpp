#include "Game/MainScene.h"
#include "Entities/PlayerEntity.h"
#include "Components/TransformComponent.h"
#include "Systems/RenderSystem.h"

void MainScene::load(ECSManager& ecs) {
    auto player = createPlayer(ecs);
}

void MainScene::update(float deltaTime) {
}
