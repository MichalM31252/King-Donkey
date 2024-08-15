extern "C" {
#include "CollisionResolver.h"
}

CollisionResolver::CollisionResolver() {
    this->gameObjectContainer = std::make_unique<GameObjectContainer>();
    this->screenManager = std::make_unique<ScreenManager>();
}

CollisionResolver::CollisionResolver(std::unique_ptr<GameObjectContainer> gameObjectContainer, std::unique_ptr<ScreenManager> screenManager) {
    this->gameObjectContainer = std::move(gameObjectContainer);
    this->screenManager = std::move(screenManager);
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

void CollisionResolver::handlePlayerCollisionWithBarrel(std::unique_ptr<MovableGameObject> barrel, bool* quit, int* startAnotherRound) {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
        *quit = true;
        *startAnotherRound = 1;
    }
}

void CollisionResolver::handlePlayerCollisionWithLadder() {
    for (int i = 0; i < gameObjectContainer->ladderHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i]->destRect)) {
            gameObjectContainer->player->isInsideLadder = true;
            return;
        }
    }
    gameObjectContainer->player->isInsideLadder = false;
    gameObjectContainer->player->isClimbing = false;
}

void CollisionResolver::handleCollisionWithJumping() {
    if (gameObjectContainer->player->isFalling) {
        gameObjectContainer->player->stopFalling();
        gameObjectContainer->player->checkIfJumpPossible = false;
    }
    if (!gameObjectContainer->player->isFalling && gameObjectContainer->player->checkIfJumpPossible) {
        gameObjectContainer->player->startJumping();
        gameObjectContainer->player->checkIfJumpPossible = false;
    }
}

void CollisionResolver::handleCollisionWithPlatform(std::unique_ptr<MovableGameObject> gameObject) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    for (int i = 0; i < gameObjectContainer->platformHolder->getNumberOfElements(); i++) {
		if (CollisionDetector::isGameObjectInsidePlatform(std::move(gameObject), std::move(gameObjectContainer->platformHolder->platforms[i]))) { // ERROR, ERROR
            gameObject->ypos--;
            yPosition--;
        }
    }
}

void CollisionResolver::handlePlayerCollision() {
	std::unique_ptr<Player> player = std::move(gameObjectContainer->player);

	handleCollisionWithPlatform(std::move(player)); // ERROR
    handlePlayerCollisionWithKong();
    handlePlayerCollisionWithPrincess();
    handlePlayerCollisionWithLadder();

    if (!player->isClimbing) {
		if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(std::move(player), std::move(gameObjectContainer->platformHolder))) { // ERROR, ERROR
            screenManager->loadTexture(player, PLAYER_1_FILENAME);
            handleCollisionWithJumping();
        }
        else {
			PhysicsManager::handleFallingForPlayer(std::move(player), screenManager->deltaTime); // ERROR
        }
        if (player->isJumping) {
            player->jump(screenManager->deltaTime);
        }
        if (player->isJumping && player->ypos <= player->jumpHeightStop) {
            player->stopJumping();
            player->startFalling();
        }
    }
}

void CollisionResolver::handleBarrelsCollision(bool* quit, int* startAnotherRound) {
    for (int i = 0; i < gameObjectContainer->barrelFactory->barrelHolder->getNumberOfElements(); i++) {
        gameObjectContainer->barrelFactory->barrelHolder->getNumberOfElements();
		std::unique_ptr<MovableGameObject> barrel = std::move(gameObjectContainer->barrelFactory->barrelHolder->barrels[i]); // ERROR

		handlePlayerCollisionWithBarrel(std::move(barrel), quit, startAnotherRound); // ERROR
		handleCollisionWithPlatform(std::move(barrel)); // ERROR

		if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(std::move(barrel), std::move(gameObjectContainer->platformHolder))) { // ERROR, ERROR
            if (barrel->isFalling) {
                barrel->stopFalling();
                barrel->stopMove();
            }
            barrel->startMovingAtSpeed(DEFAULT_BARREL_SPEED);
            barrel->startMovingRight(screenManager->deltaTime);
        }
        else {
            PhysicsManager::handleFalling(std::move(barrel), screenManager->deltaTime);
        }
        barrel->update(screenManager->deltaTime);
    }
}

void CollisionResolver::closeGame() {
    SDL_Quit();
    exit(0);
}