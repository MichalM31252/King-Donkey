extern "C" {
#include "PhysicsManager.h"
}

void PhysicsManager::handleFallingForPlayer(std::unique_ptr<Player> player, double deltaTime) {
	if (!player->isJumping) {
		handleFalling(std::move(player), deltaTime);
	}
}

void PhysicsManager::handleFalling(std::unique_ptr<MovableGameObject> gameObject, double deltaTime) {
	gameObject->startFalling();
	gameObject->accumulatedMoveDown += deltaTime * gameObject->gravity;
	int pixelsToMove = static_cast<int>(gameObject->accumulatedMoveDown);
	if (pixelsToMove >= 1) {
		gameObject->ypos += pixelsToMove;
		gameObject->accumulatedMoveDown -= pixelsToMove;
	}
}