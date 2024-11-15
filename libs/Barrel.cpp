#include "Barrel.h"
#include "ScreenManager.h" // Fix in the future

Barrel::Barrel() {
	this->currentSpriteId = 1;
	this->distanceTravelledFromLastSpriteChange = 5;
}

void Barrel::update(double deltaTime) {
	this->updatePosition();
	accumulateDistance(deltaTime);
	stayInBounds();
	updatePositionCoordinates();
}

void Barrel::updatePosition() {
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

	distanceTravelledFromLastSpriteChange += pixelsToMove;
}

// move to animation manager ? Fix in the future
void Barrel::loadNextSprite() {
	if (this->currentSpriteId == 1) {
		ScreenManager::loadTexture(this, BARREL_1_FILENAME);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 2) {
		ScreenManager::loadTexture(this, BARREL_2_FILENAME);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 3) {
		ScreenManager::loadTexture(this, BARREL_3_FILENAME);
		this->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, BARREL_4_FILENAME);
		this->currentSpriteId = 1;
	}
}
