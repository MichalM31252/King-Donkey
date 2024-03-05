extern "C" {
#include "./PhysicsManager.h"
#include "./Constants.h"
}

PhysicsManager::PhysicsManager() {
	gravity = DEFAULT_GRAVITY;
	isFalling = true;
}

void handleFalling(DynamicGameObject* dynamicGameObject) {
	if (!dynamicGameObject->isJumping) {
		dynamicGameObject->startFalling();

		dynamicGameObject->accumulatedYMove += deltaTime * dynamicGameObject->gravity;
		int pixelsToMove = dynamicGameObject->accumulatedYMove / 1;
		if (pixelsToMove >= 1) {
			dynamicGameObject->ypos += 1;
			dynamicGameObject->accumulatedYMove -= 1;
		}
	}
}

