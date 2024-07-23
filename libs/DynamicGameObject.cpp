extern "C" {
#include "DynamicGameObject.h"
#include "ScreenManager.h" // Temporary solution
}

// CURRENT TASK - remove: isPlayer, isClimbing, isJumping from this class

DynamicGameObject::DynamicGameObject() {
	currentDirectionOfMovement = -1; // 0 - up , 1 - right, 2 - down, 3 - left

	accumulatedMoveDown = 0;
	accumulatedMoveLeft = 0;
	accumulatedMoveRight = 0;
	accumulatedMoveUp = 0;

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
	if (currentDirectionOfMovement == 0) { // up
		if (isClimbing) {
			accumulatedMoveUp += deltaTime * objectSpeed;
		}
	}
	else if (currentDirectionOfMovement == 1) { // right
		accumulatedMoveRight += deltaTime * objectSpeed;
	}
	else if (currentDirectionOfMovement == 2) { // down
		if (isClimbing) {
			accumulatedMoveDown += deltaTime * objectSpeed;
		}
	}
	else if (currentDirectionOfMovement == 3) { // left
		accumulatedMoveLeft += deltaTime * objectSpeed;
	}
	else {
		return;
	}
}

void DynamicGameObject::updatePosition() {

	//xpos += 1;
	//accumulatedMoveRight -= 1;

	if (accumulatedMoveRight > 1.0) { // right
		int pixelsToMove = accumulatedMoveRight / 1;
		if (pixelsToMove > 1) {
			xpos += 1;
			accumulatedMoveRight -= 1;
		}
	}
	if (accumulatedMoveDown > 1.0) { // down
		int pixelsToMove = accumulatedMoveDown / 1;
		if (pixelsToMove > 1) {
			ypos += 1;
			accumulatedMoveDown -= 1;
		}
	}
	if (accumulatedMoveLeft > 1.0) { // left
		int pixelsToMove = accumulatedMoveLeft / 1;
		if (pixelsToMove > 1) {
			xpos -= 1;
			accumulatedMoveLeft -= 1;
		}
	}
	if (accumulatedMoveUp > 1.0) { // up
		int pixelsToMove = accumulatedMoveUp / 1;
		if (pixelsToMove > 1) {
			ypos -= 1;
			accumulatedMoveUp -= 1;
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

void DynamicGameObject::startMovingUp(double deltaTime) {
	currentDirectionOfMovement = 0;
}

void DynamicGameObject::startMovingRight(double deltaTime) {
	currentDirectionOfMovement = 1;
}

void DynamicGameObject::startMovingDown(double deltaTime) {
	currentDirectionOfMovement = 2;
}

void DynamicGameObject::startMovingLeft(double deltaTime) {
	currentDirectionOfMovement = 3;
}

void DynamicGameObject::stopMove() {
	accumulatedMoveRight = 0;
	accumulatedMoveLeft = 0;
	accumulatedMoveUp = 0;
	accumulatedMoveDown = 0;

	currentDirectionOfMovement = -1;
	objectSpeed = 0;
}

void DynamicGameObject::startFalling() {
	isFalling = true;
}

void DynamicGameObject::stopFalling() {
	isFalling = false;
}