#include "Entities/PlayerEntity.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/InputComponent.h"
#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/ControlSystem.h"
#include "Systems/SimpleRpgMovementInput.h"
#include <cstdlib>  // Para rand()
#include <ctime>    // Para time()

std::shared_ptr<Entity> createPlayer(ECSManager& ecs) {
    // Inicializa o gerador de número aleatório (só na primeira vez)
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    const int screenWidth = 600;
    const int screenHeight = 400;
    const int playerWidth = 15;
    const int playerHeight = 15;

    float randomX = static_cast<float>(std::rand() % (screenWidth - playerWidth));
    float randomY = static_cast<float>(std::rand() % (screenHeight - playerHeight));

    auto player = ecs.createEntity();

    auto transform = std::make_shared<TransformComponent>(randomX, randomY, playerWidth, playerHeight);
    auto velocity = std::make_shared<VelocityComponent>(0.0f, 0.0f);
    auto input = std::make_shared<InputComponent>();

    player->addComponent<TransformComponent>(transform);
    player->addComponent<VelocityComponent>(velocity);
    player->addComponent<InputComponent>(input);

    auto renderSystem = ecs.getSystem<RenderSystem>();
    if (renderSystem) {
        renderSystem->addEntity(player);
    }

    auto movementSystem = ecs.getSystem<MovementSystem>();
    if (movementSystem) {
        movementSystem->addEntity(player);
    }

    auto control = ecs.getSystem<ControlSystem>();
    if (control) {
        control->addEntity(player);
    }

    auto inputMovement = ecs.getSystem<SimpleRpgMovementInput>();
    if (inputMovement) {
        inputMovement->addEntity(player);
    }

    return player;
}
