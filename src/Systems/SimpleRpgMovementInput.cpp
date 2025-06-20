#include "Systems/SimpleRpgMovementInput.h"
#include "ECS/Entity.h"
#include "Components/InputComponent.h"
#include "Components/VelocityComponent.h"
#include <cmath>  // Para sqrtf()

void SimpleRpgMovementInput::update(float deltaTime)
{
    (void)deltaTime;

    for (auto& entity : entities) {
        auto input = entity->getComponent<InputComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();

        if (input && velocity) {
            float moveX = 0.0f;
            float moveY = 0.0f;

            const float speed = 100.0f;
            const float epsilon = 0.0001f;  // Para evitar divisão por zero e vibração

            if (input->up) {
                moveY -= 1.0f;
            }
            if (input->down) {
                moveY += 1.0f;
            }
            if (input->left) {
                moveX -= 1.0f;
            }
            if (input->right) {
                moveX += 1.0f;
            }

            float lengthSquared = (moveX * moveX) + (moveY * moveY);

            if (lengthSquared > epsilon) {
                float length = std::sqrt(lengthSquared);
                velocity->velocity.x = (moveX / length) * speed;
                velocity->velocity.y = (moveY / length) * speed;
            } else {
                velocity->velocity.x = 0.0f;
                velocity->velocity.y = 0.0f;
            }
        }
    }
}
