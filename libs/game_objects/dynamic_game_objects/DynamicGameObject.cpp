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

void DynamicGameObject::update(double deltaTime) { // break this up into smaller functions
	if (isFalling) {
		ypos += deltaTime * gravity;
	}
	if (!canLeaveScreen) {
		if (xpos < STARTING_X) { // left
			xpos = STARTING_X;
		}
		if (xpos + destRect.w > SCREEN_WIDTH) { // right
			xpos = SCREEN_WIDTH - destRect.w;
		}
		if (ypos + destRect.h > SCREEN_HEIGHT) { // bottom
			ypos = SCREEN_HEIGHT - destRect.h;
		}
		if (ypos < STARTING_Y + TOP_BAR_HEIGHT) { // top
			ypos = STARTING_Y + TOP_BAR_HEIGHT;
		}
	}
	if (objectSpeed > 0) {
		xpos += deltaTime * objectSpeed * currentDirectionOfMovementHorizontal;
		ypos += deltaTime * objectSpeed * currentDirectionOfMovementVertical;
	}

	destRect.x = xpos;
	destRect.y = ypos;

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