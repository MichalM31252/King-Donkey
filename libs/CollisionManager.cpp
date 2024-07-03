extern "C" {
#include "CollisionManager.h"
}

CollisionManager::CollisionManager() {
	this->gameObjectContainer = new GameObjectContainer();
}

CollisionManager::CollisionManager(GameObjectContainer* gameObjectContainer) {
	this->gameObjectContainer = gameObjectContainer;
}

bool CollisionManager::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionManager::isPointAPartOfLine(const int x, const int y, Platform* platform) { // make this function check for x1 and x2 
	double a = platform->y2pos - platform->y1pos;
	double b = platform->x1pos - platform->x2pos;
	double c = a * platform->x1pos + b * platform->y1pos;
	
	// Ax + By = C
	if ( a * x + b * y == c) { // is point part of the line
		if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) {
			return true;
		}
	}
	return false;
}



bool CollisionManager::isRectInsideLadder(SDL_Rect playerDestRect, SDL_Rect ladderDestRect) { // a is player for ex, b is ladder // poor readability
	if (playerDestRect.x >= ladderDestRect.x && playerDestRect.x + playerDestRect.w <= ladderDestRect.x + ladderDestRect.w) {
		if (playerDestRect.y + playerDestRect.h <= ladderDestRect.y + ladderDestRect.h && playerDestRect.y + playerDestRect.h >= ladderDestRect.y) {
			return true;
		}
	}
	return false;
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithKong() {
	if (isCollisionBetweenRects( gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithPrincess() {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithLadder(int* flagLadder) {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			*flagLadder = 1;
		}
	}
	if (*flagLadder) {
		gameObjectContainer->player->isInsideLadder = true;
	}
	else {
		gameObjectContainer->player->isInsideLadder = false;
		gameObjectContainer->player->isClimbing = false;
	}
}


// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithJumping() {
	if (gameObjectContainer->player->isFalling) {
		gameObjectContainer->player->stopFalling();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
	if (!gameObjectContainer->player->isFalling && gameObjectContainer->player->checkIfJumpPossible) {
		gameObjectContainer->player->startJumping();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform) {
	// check bottom left corner
	// check bottom right corner
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	for (int i = 0; i < gameObjectContainer->platformHolder->numberOfElements; i++) {

		//bottom left corner 
		if (isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, &gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, &gameObjectContainer->platformHolder->platforms[i])) { // isPointOnTopOfLine
			*flagPlatform = 1;
		}

		//bottom right corner 
		if (isPointAPartOfLine(xPositionBottomRightCorner, yPosition, &gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, &gameObjectContainer->platformHolder->platforms[i])) {// isPointOnTopOfLine
			*flagPlatform = 1;
		}
	}
}

void CollisionManager::closeGame() {
	SDL_Quit();
	exit(0);
}