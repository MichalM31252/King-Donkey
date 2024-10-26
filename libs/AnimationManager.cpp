#include "AnimationManager.h"

AnimationManager::AnimationManager(std::shared_ptr<GameObjectContainer> gameObjectContainer)
    : gameObjectContainer(std::move(gameObjectContainer))
{
}

void AnimationManager::handleAnimations() {
    handlePlayerAnimation();
    handleAllBarrelsAnimation();
}

void AnimationManager::handlePlayerAnimation() {
    auto player = gameObjectContainer->player;

    // RUNNING
    if ((player->currentDirectionOfMovementX == DirectionX::LEFT || player->currentDirectionOfMovementX == DirectionX::RIGHT) && player->velocityX > 0 && player->distanceTravelledFromLastRunningSprite >= 20) {
        player->loadNextRunningSprite();
        player->distanceTravelledFromLastRunningSprite -= 20;
        return;
    }

    // JUMPING
    if (player->isJumping || player->isFalling) {
        player->loadJumpingSprite();
        return;
    }

    // CLIMBING
    if (player->isClimbing) {
        if (player->distanceTravelledFromLastClimbingSprite >= 20 && player->velocityY > 0) {
            player->loadNextClimbingSprite();
            player->distanceTravelledFromLastClimbingSprite -= 20;
        }
        return;
    }

    // IDLE    
    if (player->velocityX == 0 && player->velocityY == 0 && !player->isJumping) {
        player->loadIdleSprite();
        return;
    }
}

void AnimationManager::handleAllBarrelsAnimation() const {
    for (const auto& barrel : gameObjectContainer->barrelContainer->barrels) {
        if (barrel->distanceTravelledFromLastSpriteChange >= 5) {
            barrel->loadNextSprite();
            barrel->distanceTravelledFromLastSpriteChange -= 5;
        }
    }
}