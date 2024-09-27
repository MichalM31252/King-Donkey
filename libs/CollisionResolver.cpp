#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
    : gameObjectContainer(new GameObjectContainer())
{
}

CollisionResolver::CollisionResolver(GameObjectContainer* gameObjectContainer)
    : gameObjectContainer(gameObjectContainer)
{
}

void CollisionResolver::handlePlayerCollisionWithKong() const {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
        closeGame();
    }
}

void CollisionResolver::handlePlayerCollisionWithPrincess() const {
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
    for (int i = 0; i < gameObjectContainer->ladderContainer->getNumberOfElements(); i++) {
        if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->ladderContainer->ladders[i]->destRect)) {
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
    for (int i = 0; i < gameObjectContainer->platformContainer->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectInsidePlatform(gameObject, gameObjectContainer->platformContainer->platforms[i])) {
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
        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(player, gameObjectContainer->platformContainer)) {
            
            // MOVE THIS TO UPDATE TEXTURES
            
            ScreenManager::loadTexture(player, PLAYER_1_FILENAME);
            
            //
            
            handleCollisionWithJumping();
        }
        if (player->isJumping && player->ypos <= player->jumpHeightStop) {
            player->stopJumping();
            player->startFalling();
        }
    }
}

void CollisionResolver::handleBarrelsCollision(bool* quit, int* startAnotherRound) {
    for (int i = 0; i < gameObjectContainer->barrelContainer->getNumberOfElements(); i++) {
        MovableGameObject* barrel = gameObjectContainer->barrelContainer->barrels[i];

        handlePlayerCollisionWithBarrel(barrel, quit, startAnotherRound);
        handleCollisionWithPlatform(barrel);

        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(barrel, gameObjectContainer->platformContainer)) {
            if (barrel->isFalling) {
                barrel->stopFalling();
                barrel->stopMove();
            }
            barrel->startMovingAtSpeed(DEFAULT_BARREL_SPEED);
            barrel->startMovingRight();
        }
    }
}

[[noreturn]] void CollisionResolver::closeGame() const {
    SDL_Quit();
    exit(0);
}