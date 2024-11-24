#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
    : gameObjectContainer(std::make_shared<GameObjectContainer>())
{
}

CollisionResolver::CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer)
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

void CollisionResolver::handlePlayerCollisionWithBarrel(std::shared_ptr<Barrel> barrel, bool* quit, GameTime* gameTime) const{
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
        *quit = true;
		gameTime->pause();
    }
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

void CollisionResolver::handleCollisionWithPlatform(const std::shared_ptr<MovableGameObject>& gameObject) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    for (int i = 0; i < gameObjectContainer->platformContainer->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectInsidePlatform(gameObject, gameObjectContainer->platformContainer->platforms[i])) {
            gameObject->ypos--;
            yPosition--;
        }
    }
}

void CollisionResolver::handlePlayerCollision() {
    auto player = gameObjectContainer->player;

    handleCollisionWithPlatform(player);
    handlePlayerCollisionWithKong();
    handlePlayerCollisionWithPrincess();

    if (!player->isClimbing) {
        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(player, gameObjectContainer->platformContainer)) {
            handleCollisionWithJumping();
        }
        if (player->isJumping && player->ypos <= player->jumpHeightStop) {
            player->stopJumping();
            player->startFalling();
        }
    }
}

void CollisionResolver::handleBarrelsCollision(bool* quit, GameTime* gameTime) {
    for (int i = 0; i < gameObjectContainer->barrelContainer->getNumberOfElements(); i++) {
        auto barrel = gameObjectContainer->barrelContainer->barrels[i];

        handlePlayerCollisionWithBarrel(barrel, quit, gameTime);
        handleCollisionWithPlatform(barrel);

        if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(barrel, gameObjectContainer->platformContainer)) {
            if (barrel->isFalling) {
                barrel->stopFalling();
                barrel->stopMove();
            }
            barrel->startMovingHorizontallyAtSpeed(DEFAULT_BARREL_SPEED);
            barrel->startMovingRight();
        }
    }
}


[[noreturn]] void CollisionResolver::closeGame() const {
    SDL_Quit();
    exit(0);
}