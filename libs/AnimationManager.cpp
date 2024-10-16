#include "AnimationManager.h"

AnimationManager::AnimationManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer)
{
}

void AnimationManager::handleAnimations(double deltaTime) {
	handlePlayerAnimation();
	handleBarrelAnimation();
}

// 
void AnimationManager::handlePlayerAnimation() {
	Player* player = gameObjectContainer->player;

	// RUNNING
	if ((player->directionOfMovementX == LEFT || player->directionOfMovementX == RIGHT) && player->velocityX > 0) {
		if (player->distanceTravelledFromLastRunningSprite >= 20) {
			player->loadNextRunningSprite();
			player->distanceTravelledFromLastRunningSprite -= 20;
			return;
		}
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
	if (player->velocityX == 0 && player->velocityY == 0 && !player->isJumping) { // refactor jumping mechanism so this actually works
		player->loadIdleSprite();
		return;
	}

	// 4 functions, isPlayerRunning, isPlayerJumping, isPlayerClimbing, isPlayerIdle


	// horizontally it saves the last direction inside directionof movement x but it does not save the last direction of movement y
}

void AnimationManager::handleBarrelAnimation() { // barrels, because its all barrels
	if (gameObjectContainer->barrelContainer->getNumberOfElements() == 0) {
		return;
	}

	for (auto barrel : gameObjectContainer->barrelContainer->barrels) {
		if (barrel->distanceTravelledFromLastSpriteChange >= 5) {
			barrel->loadNextSprite();
			barrel->distanceTravelledFromLastSpriteChange -= 5;
		}
	}

}
