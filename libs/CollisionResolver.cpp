#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
    : gameObjectContainer(std::make_shared<GameObjectContainer>())
{
}

CollisionResolver::CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer)
    : gameObjectContainer(gameObjectContainer)
{
}



// CREATE ONE BIGGER FUNCTION NOT JUST FOR PLAYER



// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
void CollisionResolver::handlePlayerCollisionWithKong() const {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
        closeGame();
    }
}

// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
void CollisionResolver::handlePlayerCollisionWithPrincess() const {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
        closeGame();
    }
}

// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
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

}

void CollisionResolver::handlePlayerCollision() {
    auto player = gameObjectContainer->player;

    handleCollisionWithPlatform(player);
    // refactor this to handleCollisionWithKong() and based on the type of the given object handle the function
    handlePlayerCollisionWithKong();
	// refactor this to handleCollisionWithPrincess() and based on the type of the given object handle the function
    handlePlayerCollisionWithPrincess();

    // HANDLE JUMPING MECHANISM WAS HERE FOR SOME REASON
    // handlePlayerJumping();
}

void CollisionResolver::handleBarrelsCollision(GameState* gameState) {

}


[[noreturn]] void CollisionResolver::closeGame() const {
    SDL_Quit();
    exit(0);
}