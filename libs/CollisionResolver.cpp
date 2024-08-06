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

void CollisionResolver::handlePlayerCollisionWithKong() {
	if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

void CollisionResolver::handlePlayerCollisionWithPrincess() {
	if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

void CollisionResolver::handlePlayerCollisionWithBarrel(MovableGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

void CollisionResolver::handlePlayerCollisionWithLadder() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (CollisionDetector::isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i].destRect)) {
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

void CollisionResolver::handleCollisionWithPlatform(MovableGameObject* gameObject) {
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	for (int i = 0; i < gameObjectContainer->platformHolder->numberOfElements; i++) {		
		if (CollisionDetector::isGameObjectInsidePlatform(gameObject, &gameObjectContainer->platformHolder->platforms[i])) {
			gameObject->ypos--;
			yPosition--;
		}
	}
}

void CollisionResolver::handlePlayerCollision() { // player collision
	Player* player = gameObjectContainer->player;

	handleCollisionWithPlatform(gameObjectContainer->player);
	handlePlayerCollisionWithKong();
	handlePlayerCollisionWithPrincess();
	handlePlayerCollisionWithLadder();

	// write a function is player climbing
	if (!player->isClimbing) {
		if (CollisionDetector::isGameObjectInsideAnyPlatform(player, gameObjectContainer->platformHolder)) {
			screenManager->loadTexture(player, PLAYER_1_FILENAME);
			// what does this function do?
			handleCollisionWithJumping();
		}
		else {
			// again start falling not handle falling
			PhysicsManager::handleFallingForPlayer(player, screenManager->deltaTime);
		}
		if (player->isJumping) {
			// this should be renamed to start jumping
			player->jump(screenManager->deltaTime);
		}
		if (player->isJumping && player->ypos <= player->jumpHeightStop) {
			player->stopJumping();
			player->startFalling();
		}
	}
}

void CollisionResolver::handleBarrelsCollision(bool* quit, int* startAnotherRound) {
	for (int i = 0; i < gameObjectContainer->barrelFactory->barrelHolder->numberOfElements; i++) {
		MovableGameObject* barrel = &gameObjectContainer->barrelFactory->barrelHolder->barrels[i];

		handlePlayerCollisionWithBarrel(barrel, quit, startAnotherRound);
		handleCollisionWithPlatform(barrel);

		if (CollisionDetector::isGameObjectOnTopOfPlatform(barrel, &gameObjectContainer->platformHolder->platforms[i])) {
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