#include "ScreenManager.h" 
#include "MovableGameObject.h"

MovableGameObject::MovableGameObject() {
	currentDirectionOfMovement = -1; // 0 - up , 1 - right, 2 - down, 3 - left
	accumulatedMoveDown = 0;
	accumulatedMoveLeft = 0;
	accumulatedMoveRight = 0;
	accumulatedMoveUp = 0;
	canLeaveScreen = false;
	objectSpeed = 0;
	currentSpriteId = 1;
	gravity = DEFAULT_GRAVITY; // physics manager ??
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
		auto pixelsToMove = (int)accumulatedMoveRight;
		xpos += pixelsToMove;
		accumulatedMoveRight -= pixelsToMove;
	}
	if (accumulatedMoveDown > 1.0f) {
		auto pixelsToMove = (int)accumulatedMoveDown;
		ypos += pixelsToMove;
		accumulatedMoveDown -= pixelsToMove;
	}
	if (accumulatedMoveLeft > 1.0f) {
		auto pixelsToMove = (int)accumulatedMoveLeft;
		xpos -= pixelsToMove;
		accumulatedMoveLeft -= pixelsToMove;
	}
	if (accumulatedMoveUp > 1.0f) {
		auto pixelsToMove = (int)accumulatedMoveUp;
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

void MovableGameObject::updatePositionCoordinates() {
	destRect.x = xpos;
	destRect.y = ypos;
}

void MovableGameObject::update(double deltaTime) { // break this up into smaller functions
	updatePosition();
	startAccumulatingDistance(deltaTime);
	stayInBounds();
	updatePositionCoordinates();
}

void MovableGameObject::startMovingAtSpeed(double speed) {
	objectSpeed = speed;
}

void MovableGameObject::startMovingUp() {
	currentDirectionOfMovement = 0;
}

void MovableGameObject::startMovingRight() {
	currentDirectionOfMovement = 1;
}

void MovableGameObject::startMovingDown() {
	currentDirectionOfMovement = 2;
}

void MovableGameObject::startMovingLeft() {
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