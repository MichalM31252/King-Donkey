#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(std::shared_ptr<GameObjectContainer> gameObjectContainer)
	: gameObjectContainer(gameObjectContainer)
{
}

void PhysicsManager::handleFallingForPlayer(double deltaTime) {
    if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(gameObjectContainer->player, gameObjectContainer->platformContainer) && !gameObjectContainer->player->isJumping && !gameObjectContainer->player->isClimbing) {
        forceFalling(gameObjectContainer->player, deltaTime);
    }
}

void PhysicsManager::handleFallingForBarrels(double deltaTime) {
	for (int i = 0; i < gameObjectContainer->barrelContainer->getNumberOfElements(); i++) {
		auto* barrel = gameObjectContainer->barrelContainer->barrels[i];
        if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(barrel, gameObjectContainer->platformContainer)) {
            forceFalling(barrel, deltaTime);
        }
	}
}

void PhysicsManager::forceFalling(MovableGameObject* gameObject, double deltaTime) const {
    gameObject->startFalling();
    gameObject->accumulatedMoveDown += deltaTime * gameObject->gravity;
    auto pixelsToMove = static_cast<int>(gameObject->accumulatedMoveDown);
    if (pixelsToMove >= 1) {
        gameObject->ypos += pixelsToMove;
        gameObject->accumulatedMoveDown -= pixelsToMove;
    }
}