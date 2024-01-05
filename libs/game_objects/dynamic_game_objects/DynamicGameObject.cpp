extern "C" {
#include "./DynamicGameObject.h"
}

// objectSpeed should be moved to physics

DynamicGameObject::DynamicGameObject() {
	canLeaveScreen = false;
	gravity = DEFAULT_GRAVITY;
	isFalling = false;
	currentDirectionOfMovementHorizontal = 0; // 1 = right, -1 = left
	currentDirectionOfMovementVertical = 0; // 1 = down, -1 = up
	objectSpeed = 0;
}

void DynamicGameObject::update(double deltaTime) {
	if (isFalling) {
		destRect.y += deltaTime * gravity;
	}
	if (!canLeaveScreen) {
		if (destRect.x < STARTING_X) {
			destRect.x = STARTING_X;
		}
		else if (destRect.x > SCREEN_WIDTH) {
			destRect.x = STARTING_X;
		}
	}
	if (objectSpeed > 0) {
		destRect.x += deltaTime * objectSpeed * currentDirectionOfMovementHorizontal;
		destRect.y += deltaTime * objectSpeed * currentDirectionOfMovementVertical;
	}
}

void DynamicGameObject::moveStart() {
	objectSpeed = DEFAULT_PLAYER_SPEED;
}

void DynamicGameObject::startMovingLeft(double deltaTime) {
	currentDirectionOfMovementHorizontal = -1;
	currentDirectionOfMovementVertical = 0;
}

void DynamicGameObject::startMovingRight(double deltaTime) {
	currentDirectionOfMovementHorizontal = 1;
	currentDirectionOfMovementVertical = 0;
}

void DynamicGameObject::startMovingUp(double deltaTime) {
	currentDirectionOfMovementVertical = -1;
	currentDirectionOfMovementHorizontal = 0;
}

void DynamicGameObject::startMovingDown(double deltaTime) { 	// under the circumstance that a player is on the ladder
	currentDirectionOfMovementVertical = 1;
	currentDirectionOfMovementHorizontal = 0;
}

void DynamicGameObject::moveStop() {
	objectSpeed = 0;
}

void DynamicGameObject::startFalling() {
	isFalling = true;
}

void DynamicGameObject::stopFalling() {
	isFalling = false;
}