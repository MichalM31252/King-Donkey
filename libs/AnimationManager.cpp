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

// based on distance traveled // is it possible to use a map to assign to every game object its last reference point??
void AnimationManager::handlePlayerAnimation() {
	Player* player = gameObjectContainer->player;

	if (player->directionOfMovementX == LEFT || player->directionOfMovementX == RIGHT) {
		if (player->isJumping || player->isFalling) {
			player->loadJumpingSprite();
		}
		else if (player->distanceTravelledFromLastRunningSprite >= 20) { // after a specific amount of time change sprite
			player->loadNextRunningSprite();
			player->distanceTravelledFromLastRunningSprite -= 20;
		}
		else if (player->velocityX == 0) {
			player->loadIdleSprite();
		}
	}

	if (player->directionOfMovementY == UP || player->directionOfMovementY == DOWN) {
		if (player->isClimbing) {
			if (player->distanceTravelledFromLastClimbingSprite >= 20 && player->velocityY > 0) {
				player->loadNextClimbingSprite();
				player->distanceTravelledFromLastClimbingSprite -= 20;
			}
		}
	}
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
