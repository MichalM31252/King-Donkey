extern "C" {
#include "PhysicsManager.h"
}

void PhysicsManager::handleFalling(DynamicGameObject* dynamicGameObject, double deltaTime) {
	if (!dynamicGameObject->isJumping) {
		dynamicGameObject->startFalling();
		dynamicGameObject->accumulatedMoveDown += deltaTime * dynamicGameObject->gravity;
		int pixelsToMove = dynamicGameObject->accumulatedMoveDown / 1;
		if (pixelsToMove >= 1) {
			dynamicGameObject->ypos += 1;
			dynamicGameObject->accumulatedMoveDown -= 1;
		}
	}
}