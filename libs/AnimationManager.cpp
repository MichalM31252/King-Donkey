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

	if (player->currentDirectionOfMovement == 1) {
		if (player->isJumping || player->isFalling) {
			player->loadJumpingSprite();
		}
		if (player->isClimbing) {
			// here check the last reference point and based on that decide if the program should change the sprite
			player->loadClimbingSprite();
		}
		if (player->distanceTravelledFromLastRunningSprite >= 20 && player->objectSpeed > 0) { // after a specific amount of time change sprite
			player->loadNextRunningSprite();
			player->distanceTravelledFromLastRunningSprite -= 20;
		}
		if (player->objectSpeed == 0) {
			player->loadIdleSprite();
		}
	}
	if (player->currentDirectionOfMovement == 3) {
		// works
	}

	// teraz jak sie zatrzymuje (puszczasz guzik do ruszania sie) to zawsze ma direction of movement 0
	// i nie wiadomo jaka animacje dac



	// somewhere in the code add, after few seconds play idle animation
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
