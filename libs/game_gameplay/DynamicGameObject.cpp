extern "C" {
#include "../../libs/game_gameplay/DynamicGameObject.h"
}

// objectSpeed should be moved to physics

DynamicGameObject::DynamicGameObject() {
	objectSpeed = 0;
	/*physics = Physics();*/
}

void DynamicGameObject::moveStart() {
	objectSpeed = DEFAULT_PLAYER_SPEED;
}

void DynamicGameObject::moveLeft(double deltaTime) {
	destRect.x -= deltaTime * objectSpeed;
}

void DynamicGameObject::moveRight(double deltaTime) {
	destRect.x += deltaTime * objectSpeed;
}

void DynamicGameObject::moveUp(double deltaTime) {
	// under the circumstance that a player is on the ladder
	destRect.y -= deltaTime * objectSpeed;
}

void DynamicGameObject::moveDown(double deltaTime) {
	// under the circumstance that a player is on the ladder
	destRect.y += deltaTime * objectSpeed;
}

void DynamicGameObject::moveStop() {
	objectSpeed = 0;
}