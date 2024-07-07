extern "C" {
#include "CollisionManager.h"
}

CollisionManager::CollisionManager() {
	this->gameObjectContainer = new GameObjectContainer();
}

CollisionManager::CollisionManager(GameObjectContainer* gameObjectContainer, ScreenManager* screenManager) {
	this->gameObjectContainer = gameObjectContainer;
	this->screenManager = screenManager;
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
void CollisionManager::handlePlayerCollisionWithKong() {
	if (isCollisionBetweenRects( gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handlePlayerCollisionWithPrincess() {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handlePlayerCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

// MOVE TO COLLISION MANAGER
void CollisionManager::handlePlayerCollisionWithLadder() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			gameObjectContainer->player->isInsideLadder = true;
			return;
		}
	}
	gameObjectContainer->player->isInsideLadder = false;
	gameObjectContainer->player->isClimbing = false;
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
void CollisionManager::handleCollisionWithPlatform(DynamicGameObject* gameObject, int* isGameObjectInsidePlatform) {
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
			*isGameObjectInsidePlatform = 1;
		}

		//bottom right corner 
		if (isPointAPartOfLine(xPositionBottomRightCorner, yPosition, &gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, &gameObjectContainer->platformHolder->platforms[i])) {// isPointOnTopOfLine
			*isGameObjectInsidePlatform = 1;
		}
	}
}


// MOVE TO GAME OBJECT MANAGER
void CollisionManager::handlePlayerCollision() { // player collision

	Player* player = gameObjectContainer->player;
	int isPlayerInsidePlatform = 0;

	handleCollisionWithPlatform(gameObjectContainer->player, &isPlayerInsidePlatform);
	handlePlayerCollisionWithKong();
	handlePlayerCollisionWithPrincess();
	handlePlayerCollisionWithLadder();

	if (!player->isClimbing) {
		if (isPlayerInsidePlatform) {
			screenManager->loadTexture(player, PLAYER_1_FILENAME);
			handleCollisionWithJumping();
		}
		else {
			// again start falling not handle falling
			PhysicsManager::handleFalling(player, screenManager->deltaTime);
		}
		if (player->isJumping) { // handle jumping
			player->jump(screenManager->deltaTime);
		}
	}

	if (player->isJumping && player->ypos <= player->jumpHeightStop) {
		player->stopJumping();
		player->startFalling();
	}
}

// MOVE TO GAME OBJECT MANAGER
void CollisionManager::handleBarrelsCollision(bool* quit, int* startAnotherRound) {
	gameObjectContainer->barrelDispenser->updateBarrelDispenser(screenManager->deltaTime);

	for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {

		DynamicGameObject* barrel = &gameObjectContainer->barrelDispenser->barrelHolder->barrels[i];

		handlePlayerCollisionWithBarrel(barrel, quit, startAnotherRound);

		int isGameObjectInsidePlatform = 0;
		handleCollisionWithPlatform(barrel, &isGameObjectInsidePlatform);

		if (isGameObjectInsidePlatform) {
			if ((*barrel).isFalling) {
				// stopObjectFromFallingThroughPlatform
				(*barrel).stopFalling();
				(*barrel).stopMove();
			}
			(*barrel).moveStart(DEFAULT_BARREL_SPEED);
			(*barrel).startMovingRight(screenManager->deltaTime);
		}
		else {
			// idk but shououldnt this be renamed to start falling?
			PhysicsManager::handleFalling(barrel, screenManager->deltaTime); // THE PROBLEM IS HERE
		}
		(*barrel).update(screenManager->deltaTime);
	}
}

void CollisionManager::closeGame() {
	SDL_Quit();
	exit(0);
}