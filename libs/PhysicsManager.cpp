extern "C" {
#include "PhysicsManager.h"
}

void PhysicsManager::handleFallingForPlayer(Player* player, double deltaTime) {
	if (!player->isJumping) {
		handleFalling(player, deltaTime);
	}
}

void PhysicsManager::handleFalling(MovableGameObject* object, double deltaTime) {
	object->startFalling();
	object->accumulatedMoveDown += deltaTime * object->gravity;
	int pixelsToMove = static_cast<int>(object->accumulatedMoveDown);
	if (pixelsToMove >= 1) {
		object->ypos += pixelsToMove;
		object->accumulatedMoveDown -= pixelsToMove;
	}
}