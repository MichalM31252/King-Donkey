#include "AnimationManager.h"

AnimationManager::AnimationManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer)
{
}

void AnimationManager::handleAnimations(double deltaTime) {
	handlePlayerAnimation();
	handleBarrelAnimation();
	handleGorillaAnimation(deltaTime);
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

// based on distance traveled // is it possible to use a map to assign to every game object its last reference point??
void AnimationManager::handleBarrelAnimation() {
	// if dynamic game object is moving
		// after a specific amount of distance is travelled from last referance point
			// change sprite to next
}

// based on time from last sprite change
void AnimationManager::handleGorillaAnimation(double deltaTime) {
	// after a specific amount of time has passed then  
		// change sprite to next
}
