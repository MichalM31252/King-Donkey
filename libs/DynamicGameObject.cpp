extern "C" {
#include "DynamicGameObject.h"
#include "ScreenManager.h" // Temporary solution
}

// CURRENT TASK - remove: isPlayer, isClimbing, isJumping from this class

DynamicGameObject::DynamicGameObject() {
	currentDirectionOfMovementHorizontal = 0.0; // 1 = right, -1 = left
	currentDirectionOfMovementVertical = 0.0; // 1 = down, -1 = up
	accumulatedXMove = 0;
	accumulatedYMove = 0;
	canLeaveScreen = false; // leave here
	objectSpeed = 0; // leave here

	currentSpriteId = 1;
	// maybe add this to game object class since princess and donkeykong can have animations but they dont move

	gravity = DEFAULT_GRAVITY; // physics manager ??

	isClimbing = false; // player
	isJumping = false; // player

	checkIfJumpPossible = false; // player / no this should be somwhere else
	jumpHeightStop = SCREEN_HEIGHT; // player / no this should be somwhere else
}

void DynamicGameObject::startAccumulatingDistance(double deltaTime) {
	if (objectSpeed > 0) {
		accumulatedXMove += deltaTime * objectSpeed * currentDirectionOfMovementHorizontal;
		// WRITE HERE A FUNCTION TO CHECK IF PLAYER IS INSIDE A LADDER
		if (isClimbing) {
			accumulatedYMove += deltaTime * objectSpeed * currentDirectionOfMovementVertical;
		}
	}
}

void DynamicGameObject::updatePosition() {
	// WATCHOUT DIFFERENT += -= SIGNS AND VARIABLES IN EVERY IF
	// moving left, down, right, top
	if (currentDirectionOfMovementHorizontal > 0.0 || currentDirectionOfMovementVertical > 0.0) { // for positive numbers 
		if (accumulatedXMove > currentDirectionOfMovementHorizontal) { // right
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
		if (accumulatedXMove < currentDirectionOfMovementHorizontal) { // left
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
}

// logic, not screen manager
void DynamicGameObject::stayInBounds() {
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
}

void DynamicGameObject::update(double deltaTime) { // break this up into smaller functions
	startAccumulatingDistance(deltaTime);
	updatePosition();
	stayInBounds();

	// to remove these you need to merge the three methods into one and then updateObjectPosition
	destRect.x = xpos;
	destRect.y = ypos;
}

void DynamicGameObject::startMovingAtSpeed(double speed) {
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

void DynamicGameObject::startMovingDown(double deltaTime) {
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

void DynamicGameObject::startFalling() {
	isFalling = true;
}

void DynamicGameObject::stopFalling() {
	isFalling = false;
}