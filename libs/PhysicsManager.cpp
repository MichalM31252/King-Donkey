extern "C" {
#include "PhysicsManager.h"
}

void PhysicsManager::handleFallingForPlayer(Player* player, double deltaTime) {
	if (!player->isJumping) {
		player->startFalling();
		player->accumulatedMoveDown += deltaTime * player->gravity;
		int pixelsToMove = player->accumulatedMoveDown / 1;
		if (pixelsToMove >= 1) {
			player->ypos += 1;
			player->accumulatedMoveDown -= 1;
		}
	}
}

void PhysicsManager::handleFalling(MovableGameObject* movableGameObject, double deltaTime) {
	movableGameObject->startFalling();
	movableGameObject->accumulatedMoveDown += deltaTime * movableGameObject->gravity;
	int pixelsToMove = movableGameObject->accumulatedMoveDown / 1;
	if (pixelsToMove >= 1) {
		movableGameObject->ypos += 1;
		movableGameObject->accumulatedMoveDown -= 1;
	}
}