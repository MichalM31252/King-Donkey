extern "C" {
#include "../../libs/game_gameplay/DynamicGameObject.h"
}

// objectSpeed should be moved to physics

void DynamicGameObject::moveLeft(double deltaTime) {
	objectSpeed = DEFAULT_PLAYER_SPEED;
	destRect.x -= deltaTime * objectSpeed;
}

void DynamicGameObject::moveRight(double deltaTime) {
	objectSpeed = DEFAULT_PLAYER_SPEED;
	destRect.x += deltaTime * objectSpeed;
}

void DynamicGameObject::moveUp(double deltaTime) {
	// under the circumstance that a player is on the ladder
	objectSpeed = DEFAULT_PLAYER_SPEED;
	destRect.y -= deltaTime * objectSpeed;
}

void DynamicGameObject::moveDown(double deltaTime) {
	// under the circumstance that a player is on the ladder
	objectSpeed = DEFAULT_PLAYER_SPEED;
	destRect.y += deltaTime * objectSpeed;
}

void DynamicGameObject::moveStop() {
	objectSpeed = 0;
}