extern "C" {
#include "CollisionResolver.h"
}

CollisionResolver::CollisionResolver() {
	this->gameObjectContainer = new GameObjectContainer();
	this->screenManager = new ScreenManager();
}

CollisionResolver::CollisionResolver(GameObjectContainer* gameObjectContainer, ScreenManager* screenManager) {
	this->gameObjectContainer = gameObjectContainer;
	this->screenManager = screenManager;
}

bool CollisionResolver::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionResolver::isPointAPartOfLine(const int x, const int y, Platform* platform) { // make this function check for x1 and x2 
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

bool CollisionResolver::isRectInsideLadder(SDL_Rect playerDestRect, SDL_Rect ladderDestRect) { // a is player for ex, b is ladder // poor readability
	if (playerDestRect.x >= ladderDestRect.x && playerDestRect.x + playerDestRect.w <= ladderDestRect.x + ladderDestRect.w) {
		if (playerDestRect.y + playerDestRect.h <= ladderDestRect.y + ladderDestRect.h && playerDestRect.y + playerDestRect.h >= ladderDestRect.y) {
			return true;
		}
	}
	return false;
}

void CollisionResolver::handlePlayerCollisionWithKong() {
	if (isCollisionBetweenRects( gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

void CollisionResolver::handlePlayerCollisionWithPrincess() {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

void CollisionResolver::handlePlayerCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

void CollisionResolver::handlePlayerCollisionWithLadder() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			gameObjectContainer->player->isInsideLadder = true;
			return;
		}
	}
	gameObjectContainer->player->isInsideLadder = false;
	gameObjectContainer->player->isClimbing = false;
}

// WHAT DOES THIS CODE EVEN DO?
void CollisionResolver::handleCollisionWithJumping() {
	if (gameObjectContainer->player->isFalling) {
		// i think this function is called when player lands on the platform after jumping and just falling (start of the game and going left from the platform)
		gameObjectContainer->player->stopFalling();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
	if (!gameObjectContainer->player->isFalling && gameObjectContainer->player->checkIfJumpPossible) {
		// this gets called after you press space (just jumping, you cant jump again after jumping)
		gameObjectContainer->player->startJumping();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
}

void CollisionResolver::handleCollisionWithPlatform(DynamicGameObject* gameObject, int* isGameObjectInsidePlatform) {
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

void CollisionResolver::handlePlayerCollision() { // player collision

	Player* player = gameObjectContainer->player;
	int isPlayerInsidePlatform = 0;

	handleCollisionWithPlatform(gameObjectContainer->player, &isPlayerInsidePlatform);
	handlePlayerCollisionWithKong();
	handlePlayerCollisionWithPrincess();
	handlePlayerCollisionWithLadder();


	if (!player->isClimbing) {
		if (isPlayerInsidePlatform) {
			screenManager->loadTexture(player, PLAYER_1_FILENAME);
			// what does this function do?
			handleCollisionWithJumping();
		}
		else {
			// again start falling not handle falling
			PhysicsManager::handleFalling(player, screenManager->deltaTime);
		}
		if (player->isJumping) { 
			// this should be renamed to start jumping
			player->jump(screenManager->deltaTime);
		}
	}

	if (player->isJumping && player->ypos <= player->jumpHeightStop) {
		player->stopJumping();
		player->startFalling();
	}
}

void CollisionResolver::handleBarrelsCollision(bool* quit, int* startAnotherRound) {
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
			(*barrel).startMovingAtSpeed(DEFAULT_BARREL_SPEED);
			(*barrel).startMovingRight(screenManager->deltaTime);
		}
		else {
			// idk but shououldnt this be renamed to start falling?
			PhysicsManager::handleFalling(barrel, screenManager->deltaTime); // THE PROBLEM IS HERE
		}
		(*barrel).update(screenManager->deltaTime);
	}
}

void CollisionResolver::closeGame() {
	SDL_Quit();
	exit(0);
}