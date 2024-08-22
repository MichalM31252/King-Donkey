#include "PhysicsManager.h"

void PhysicsManager::handleFallingForPlayer(Player* player, double deltaTime) {
    if (!player->isJumping) {
        handleFalling(player, deltaTime);
    }
}

void PhysicsManager::handleFalling(MovableGameObject* gameObject, double deltaTime) {
    gameObject->startFalling();
    gameObject->accumulatedMoveDown += deltaTime * gameObject->gravity;
    int pixelsToMove = static_cast<int>(gameObject->accumulatedMoveDown);
    if (pixelsToMove >= 1) {
        gameObject->ypos += pixelsToMove;
        gameObject->accumulatedMoveDown -= pixelsToMove;
    }
}