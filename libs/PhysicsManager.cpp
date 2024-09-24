#include "PhysicsManager.h"

PhysicsManager::PhysicsManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer)
{
}

void PhysicsManager::handleFallingForPlayer(Player* player, double deltaTime) {
    if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(player, gameObjectContainer->platformHolder) && !player->isJumping && !player->isClimbing) {
        startFalling(player, deltaTime);
    }
}

void PhysicsManager::handleFallingForBarrels(BarrelHolder* barrelHolder, double deltaTime) {
	for (int i = 0; i < barrelHolder->getNumberOfElements(); i++) {
		MovableGameObject* barrel = barrelHolder->barrels[i]; // FIX THIS // REPLACE MOVABLEGAMEOBJECT WITH BARREL
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