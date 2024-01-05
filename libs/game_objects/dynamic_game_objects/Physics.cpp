extern "C" {
#include "Physics.h"
#include "../../Constants.h"
}

Physics::Physics() {
	gravity = DEFAULT_GRAVITY;
	isFalling = false;
	currentDirectionOfMovement = 0;
}

void Physics::startFalling() {
	isFalling = true;
}

void Physics::stopFalling() {
	isFalling = false;
}