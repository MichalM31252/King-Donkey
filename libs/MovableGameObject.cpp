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
	, currentDirectionOfMovementX(CurrentDirectionOfMovementX::NONE)
	, currentDirectionOfMovementY(CurrentDirectionOfMovementY::NONE)
	, isFalling(false)
	, gravity(DEFAULT_GRAVITY)
	, currentSpriteId(1)
{
}

void MovableGameObject::accumulateDistance(double deltaTime) { // rename to accumulate distance
	if (velocityY > 0 && currentDirectionOfMovementY == CurrentDirectionOfMovementY::UP) {
		accumulatedMoveUp += deltaTime * velocityY;
	}
	else if (velocityX > 0 && currentDirectionOfMovementX == CurrentDirectionOfMovementX::RIGHT) {
		accumulatedMoveRight += deltaTime * velocityX;
	}
	else if (velocityY > 0 && currentDirectionOfMovementY == CurrentDirectionOfMovementY::DOWN) {
		accumulatedMoveDown += deltaTime * velocityY;
	}
	else if (velocityX > 0 && currentDirectionOfMovementX == CurrentDirectionOfMovementX::LEFT) {
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
	currentDirectionOfMovementY = CurrentDirectionOfMovementY::UP;
}

void MovableGameObject::startMovingRight() {
	currentDirectionOfMovementX = CurrentDirectionOfMovementX::RIGHT;
}

void MovableGameObject::startMovingDown() {
	currentDirectionOfMovementY = CurrentDirectionOfMovementY::DOWN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MovableGameObject::stopMove() {
	currentDirectionOfMovementX = CurrentDirectionOfMovementX::NONE;
	currentDirectionOfMovementY = CurrentDirectionOfMovementY::NONE;
	velocityX = 0;
	velocityY = 0;
}

void MovableGameObject::startFalling() {
	isFalling = true;
}

void MovableGameObject::stopFalling() {
	isFalling = false;
}