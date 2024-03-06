extern "C" {
#include "./PhysicsManager.h"
#include "./Constants.h"
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
}

//PhysicsManager::PhysicsManager() {
//	
//}

void PhysicsManager::handleFalling(DynamicGameObject* dynamicGameObject, double deltaTime) {
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

