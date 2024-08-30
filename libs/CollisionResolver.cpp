#include "CollisionResolver.h"


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

void CollisionResolver::handlePlayerCollisionWithBarrel(const MovableGameObject* barrel, bool* quit, int* startAnotherRound) const{
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
        *quit = true;
        *startAnotherRound = 1;
    }
}

void CollisionResolver::handlePlayerCollisionWithLadder() {
    for (int i = 0; i < gameObjectContainer->ladderHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i]->destRect)) {
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

void CollisionResolver::handleCollisionWithPlatform(MovableGameObject* gameObject) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    for (int i = 0; i < gameObjectContainer->platformHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectInsidePlatform(gameObject, gameObjectContainer->platformHolder->platforms[i])) {
            gameObject->ypos--;
            yPosition--;
        }
    }
}

void CollisionResolver::handlePlayerCollision() {
    Player* player = gameObjectContainer->player;

    handleCollisionWithPlatform(player);
    handlePlayerCollisionWithKong();
    handlePlayerCollisionWithPrincess();
    handlePlayerCollisionWithLadder();

    if (!player->isClimbing) {
        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(player, gameObjectContainer->platformHolder)) {
            ScreenManager::loadTexture(player, PLAYER_1_FILENAME);
            handleCollisionWithJumping();
        }
        else {
            PhysicsManager::handleFallingForPlayer(player, screenManager->deltaTime);
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
        MovableGameObject* barrel = gameObjectContainer->barrelFactory->barrelHolder->barrels[i];

        handlePlayerCollisionWithBarrel(barrel, quit, startAnotherRound);
        handleCollisionWithPlatform(barrel);

        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(barrel, gameObjectContainer->platformHolder)) {
            if (barrel->isFalling) {
                barrel->stopFalling();
                barrel->stopMove();
            }
            barrel->startMovingAtSpeed(DEFAULT_BARREL_SPEED);
            barrel->startMovingRight(screenManager->deltaTime);
        }
        else {
            PhysicsManager::handleFalling(barrel, screenManager->deltaTime);
        }
    }
}

void CollisionResolver::closeGame() const {
    SDL_Quit();
    exit(0);
}