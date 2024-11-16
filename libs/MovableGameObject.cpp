#include "ScreenManager.h" 
#include "MovableGameObject.h"

MovableGameObject::MovableGameObject()
	: accumulatedMoveUp(0)
	, accumulatedMoveRight(0) 
	, accumulatedMoveDown(0) 
	, accumulatedMoveLeft(0)
	, canLeaveScreen(false)
	, velocityX(0)
	, velocityY(0)
	, currentDirectionOfMovementX(DirectionX::NONE)
	, currentDirectionOfMovementY(DirectionY::NONE)
	, isFalling(false)
	, gravity(DEFAULT_GRAVITY)
{
}

void MovableGameObject::accumulateDistance(double deltaTime) {
	if (velocityY > 0 && currentDirectionOfMovementY == DirectionY::UP) {
		accumulatedMoveUp += deltaTime * velocityY;
	}
	else if (velocityX > 0 && currentDirectionOfMovementX == DirectionX::RIGHT) {
		accumulatedMoveRight += deltaTime * velocityX;
	}
	else if (velocityY > 0 && currentDirectionOfMovementY == DirectionY::DOWN) {
		accumulatedMoveDown += deltaTime * velocityY;
	}
	else if (velocityX > 0 && currentDirectionOfMovementX == DirectionX::LEFT) {
		accumulatedMoveLeft += deltaTime * velocityX;
	}
	else {
		return;
	}
}

void MovableGameObject::updatePosition() {
	int pixelsToMove = 0;
	if (accumulatedMoveRight > 1.0f) {
		pixelsToMove = (int)accumulatedMoveRight;
		xpos += pixelsToMove;
		accumulatedMoveRight -= pixelsToMove;
	}
	if (accumulatedMoveDown > 1.0f) {
		pixelsToMove = (int)accumulatedMoveDown;
		ypos += pixelsToMove;
		accumulatedMoveDown -= pixelsToMove;
	}
	if (accumulatedMoveLeft > 1.0f) {
		pixelsToMove = (int)accumulatedMoveLeft;
		xpos -= pixelsToMove;
		accumulatedMoveLeft -= pixelsToMove;
	}
	if (accumulatedMoveUp > 1.0f) {
		pixelsToMove = (int)accumulatedMoveUp;
		ypos -= pixelsToMove;
		accumulatedMoveUp -= pixelsToMove;
	}
}

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

void MovableGameObject::update(double deltaTime) {
	updatePosition();
	accumulateDistance(deltaTime);
	stayInBounds();
	updatePositionCoordinates();
}

// maybe refactor this code
////////////////////////////////

void MovableGameObject::startMovingHorizontallyAtSpeed(double speed) {
	velocityX = speed;
}

void MovableGameObject::startMovingVerticallyAtSpeed(double speed) {
	velocityY = speed;
}

void MovableGameObject::startMovingUp() {
	currentDirectionOfMovementY = DirectionY::UP;
}

void MovableGameObject::startMovingRight() {
	currentDirectionOfMovementX = DirectionX::RIGHT;
}

void MovableGameObject::startMovingLeft() {
	currentDirectionOfMovementX = DirectionX::LEFT;
}

void MovableGameObject::startMovingDown() {
	currentDirectionOfMovementY = DirectionY::DOWN;
}

//////////////////////////////////

void MovableGameObject::stopMove() {
	currentDirectionOfMovementX = DirectionX::NONE;
	currentDirectionOfMovementY = DirectionY::NONE;
	velocityX = 0;
	velocityY = 0;
}

void MovableGameObject::startFalling() {
	isFalling = true;
}

void MovableGameObject::stopFalling() {
	isFalling = false;
}