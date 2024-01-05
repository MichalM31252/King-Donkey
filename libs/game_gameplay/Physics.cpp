extern "C" {
#include "../../libs/game_gameplay/Physics.h"
#include "../../libs/game_gameplay/DynamicGameObject.h"
#include "../Constants.h"
}

Physics::Physics() {
	gravity = DEFAULT_GRAVITY;
	isFalling = false;
	currentDirectionOfMovement = 0;
}

void Physics::startFalling(DynamicGameObject* object) {
	isFalling = true;
}

void Physics::stopFalling(DynamicGameObject* object) {
	isFalling = false;
}