extern "C" {
#include "MovableGameObject.h"
#include "ScreenManager.h" // Temporary solution
}

// CURRENT TASK - remove: isPlayer, isClimbing, from this class

MovableGameObject::MovableGameObject() {
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

	checkIfJumpPossible = false; // player / no this should be somwhere else
	jumpHeightStop = SCREEN_HEIGHT; // player / no this should be somwhere else
}

void MovableGameObject::startAccumulatingDistance(double deltaTime) {
	if (currentDirectionOfMovement == 0) { // up
		accumulatedMoveUp += deltaTime * objectSpeed;
	}
	else if (currentDirectionOfMovement == 1) { // right
		accumulatedMoveRight += deltaTime * objectSpeed;
	}
	else if (currentDirectionOfMovement == 2) { // down
		accumulatedMoveDown += deltaTime * objectSpeed;
	}
	else if (currentDirectionOfMovement == 3) { // left
		accumulatedMoveLeft += deltaTime * objectSpeed;
	}
	else {
		return;
	}
}

void MovableGameObject::updatePosition() {

	if (accumulatedMoveRight > 1.0f) {
		int pixelsToMove = (int)accumulatedMoveRight;
		xpos += pixelsToMove;
		accumulatedMoveRight -= pixelsToMove;
	}

	if (accumulatedMoveDown > 1.0f) {
		int pixelsToMove = (int)accumulatedMoveDown;
		ypos += pixelsToMove;
		accumulatedMoveDown -= pixelsToMove;
	}

	if (accumulatedMoveLeft > 1.0f) {
		int pixelsToMove = (int)accumulatedMoveLeft;
		xpos -= pixelsToMove;
		accumulatedMoveLeft -= pixelsToMove;
	}

	if (accumulatedMoveUp > 1.0f) {
		int pixelsToMove = (int)accumulatedMoveUp;
		ypos -= pixelsToMove;
		accumulatedMoveUp -= pixelsToMove;
	}
}

// logic, not screen manager
void MovableGameObject::stayInBounds() {
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

void MovableGameObject::update(double deltaTime) { // break this up into smaller functions
	updatePosition();
	startAccumulatingDistance(deltaTime);
	stayInBounds();

	// to remove these you need to merge the three methods into one and then updateObjectPosition
	destRect.x = xpos;
	destRect.y = ypos;
}

void MovableGameObject::startMovingAtSpeed(double speed) {
	objectSpeed = speed;
}

void MovableGameObject::startMovingUp(double deltaTime) {
	currentDirectionOfMovement = 0;
}

void MovableGameObject::startMovingRight(double deltaTime) {
	currentDirectionOfMovement = 1;
}

void MovableGameObject::startMovingDown(double deltaTime) {
	currentDirectionOfMovement = 2;
}

void MovableGameObject::startMovingLeft(double deltaTime) {
	currentDirectionOfMovement = 3;
}

void MovableGameObject::stopMove() {
	currentDirectionOfMovement = -1;
}

void MovableGameObject::startFalling() {
	isFalling = true;
}

void MovableGameObject::stopFalling() {
	isFalling = false;
}