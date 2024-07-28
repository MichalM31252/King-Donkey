extern "C" {
#include "PhysicsManager.h"
}

void PhysicsManager::handleFalling(MovableGameObject* movableGameObject, double deltaTime) {
	if (!movableGameObject->isJumping) {
		movableGameObject->startFalling();
		movableGameObject->accumulatedMoveDown += deltaTime * movableGameObject->gravity;
		int pixelsToMove = movableGameObject->accumulatedMoveDown / 1;
		if (pixelsToMove >= 1) {
			movableGameObject->ypos += 1;
			movableGameObject->accumulatedMoveDown -= 1;
		}
	}
}