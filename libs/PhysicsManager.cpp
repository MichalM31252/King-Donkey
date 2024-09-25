#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer)
{
}

void PhysicsManager::handleFallingForPlayer(double deltaTime) {
    if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(gameObjectContainer->player, gameObjectContainer->platformHolder) && !gameObjectContainer->player->isJumping && !gameObjectContainer->player->isClimbing) {
        startFalling(gameObjectContainer->player, deltaTime);
    }
}

void PhysicsManager::handleFallingForBarrels(double deltaTime) {
	for (int i = 0; i < gameObjectContainer->barrelHolder->getNumberOfElements(); i++) {
		MovableGameObject* barrel = gameObjectContainer->barrelHolder->barrels[i]; // FIX THIS // REPLACE MOVABLEGAMEOBJECT WITH BARREL
        if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(barrel, gameObjectContainer->platformHolder)) {
            startFalling(barrel, deltaTime);
        }
	}
}

void PhysicsManager::startFalling(MovableGameObject* gameObject, double deltaTime) const {
    gameObject->startFalling();
    gameObject->accumulatedMoveDown += deltaTime * gameObject->gravity;
    auto pixelsToMove = static_cast<int>(gameObject->accumulatedMoveDown);
    if (pixelsToMove >= 1) {
        gameObject->ypos += pixelsToMove;
        gameObject->accumulatedMoveDown -= pixelsToMove;
    }
}