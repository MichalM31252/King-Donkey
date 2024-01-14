extern "C" {
#include "./DynamicGameObject.h"
}

// objectSpeed should be moved to physics
DynamicGameObject::DynamicGameObject() {
	canLeaveScreen = false;
	gravity = DEFAULT_GRAVITY;
	isFalling = true;
	currentDirectionOfMovementHorizontal = 0.0; // 1 = right, -1 = left
	currentDirectionOfMovementVertical = 0.0; // 1 = down, -1 = up
	objectSpeed = 0;
	accumulatedXMove = 0;
	accumulatedYMove = 0;
	isClimbing = false;
	isInsideLadder = false;
	checkIfJumpPossible = false;
	isJumping = false;
	jumpHeightStop = SCREEN_HEIGHT;
}

void DynamicGameObject::update(double deltaTime) { // break this up into smaller functions
	if (objectSpeed > 0) {
		accumulatedXMove += deltaTime * objectSpeed * currentDirectionOfMovementHorizontal;
		if (isClimbing) {
			accumulatedYMove += deltaTime * objectSpeed * currentDirectionOfMovementVertical;
		}
	}

	// WATCHOUT DIFFERENT += -= SIGNS AND VARIABLES IN EVERY IF
	// just add a function this is not faster this way?????
	// moving left, down, right, top
	if (currentDirectionOfMovementHorizontal > 0.0 || currentDirectionOfMovementVertical > 0.0) { // for positive numbers 
		if (accumulatedXMove > currentDirectionOfMovementHorizontal) { // right // THIS CANT BE BIGGER OR EQUAL BECAUSE WHEN STARTING IT IS ALWAYS TRUE 0 <= 0
			int pixelsToMove = accumulatedXMove / 1;
			if (pixelsToMove > 1) {
				xpos += 1;
				accumulatedXMove -= 1;
			}
		}
		if (accumulatedYMove > currentDirectionOfMovementVertical) { // down
			int pixelsToMove = accumulatedYMove / 1;
			if (pixelsToMove > 1) {
				ypos += 1;
				accumulatedYMove -= 1;
			}
		}
	}
	if (currentDirectionOfMovementHorizontal < 0.0 || currentDirectionOfMovementVertical < 0.0) { // for negative numbers
		if (accumulatedXMove < currentDirectionOfMovementHorizontal) { // 
			int pixelsToMove = accumulatedXMove / 1;
			if (pixelsToMove < 1) {
				xpos -= 1;
				accumulatedXMove += 1;
			}
		}
		if (accumulatedYMove < currentDirectionOfMovementVertical) { // up
			int pixelsToMove = accumulatedYMove / 1;
			if (pixelsToMove < 1) {
				ypos -= 1;
				accumulatedYMove += 1;
			}
		}
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

	// for each pixelsToMove check if passing through a platform !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	destRect.x = xpos;
	destRect.y = ypos;
}

void DynamicGameObject::moveStart(double speed) {
	objectSpeed = speed;
}

void DynamicGameObject::startMovingLeft(double deltaTime) {
	currentDirectionOfMovementHorizontal = -1.0;
	currentDirectionOfMovementVertical = 0.0;
}

void DynamicGameObject::startMovingRight(double deltaTime) {
	currentDirectionOfMovementHorizontal = 1.0;
	currentDirectionOfMovementVertical = 0.0;
}

void DynamicGameObject::startMovingUp(double deltaTime) {
	currentDirectionOfMovementVertical = -1.0;
	currentDirectionOfMovementHorizontal = 0.0;
}

void DynamicGameObject::startMovingDown(double deltaTime) { 	// under the circumstance that a player is on the ladder
	currentDirectionOfMovementVertical = 1.0;
	currentDirectionOfMovementHorizontal = 0.0;
}

void DynamicGameObject::stopMove() {
	accumulatedYMove = 0;
	accumulatedXMove = 0;
	currentDirectionOfMovementHorizontal = 0;
	currentDirectionOfMovementVertical = 0;
	objectSpeed = 0;
}

void DynamicGameObject::startJumping() {
	isJumping = true;
	jumpHeightStop = ypos - DEFAULT_JUMP_HEIGHT;
}

void DynamicGameObject::stopJumping() {
	isJumping = false;
	jumpHeightStop = SCREEN_HEIGHT;
	accumulatedYMove = 0;
}

void DynamicGameObject::startFalling() {
	isFalling = true;
}

void DynamicGameObject::stopFalling() {
	isFalling = false;
}

void DynamicGameObject::initJump() {
	checkIfJumpPossible = true;
	accumulatedYMove = 0;
}