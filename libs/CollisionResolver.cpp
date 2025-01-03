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

void CollisionResolver::handlePlayerCollisionWithBarrel(std::shared_ptr<Barrel> barrel, GameState* gameState) const{
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*gameState = GameState::GAME_OVER;
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
			// PLACE HERE A FUNCTION: SNAP IT ON TOP OF THE PLATFORM (THINK IT THROUGH CORRECTLY) INSTEAD OF SLOWLY PLACE IT HIGHER 
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

void CollisionResolver::handleBarrelsCollision(GameState* gameState) {
    for (int i = 0; i < gameObjectContainer->barrelContainer->getNumberOfElements(); i++) {
        auto barrel = gameObjectContainer->barrelContainer->barrels[i];

        handlePlayerCollisionWithBarrel(barrel, gameState);
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