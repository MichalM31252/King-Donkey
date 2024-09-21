#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
}

GameObjectManager::GameObjectManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer) {
}

void GameObjectManager::updateGameObjects(double deltaTime) {
	gameObjectContainer->player->update(deltaTime);
	gameObjectContainer->barrelFactory->update(deltaTime);
	gameObjectContainer->barrelFactory->barrelHolder->updateBarrels(deltaTime);
}

void GameObjectManager::handleCollisions(bool& quit, int& startAnotherRound) {
	// handle collisions
	collisionResolver->handlePlayerCollision();
	collisionResolver->handleBarrelsCollision(&quit, &startAnotherRound);
}

void GameObjectManager::updateSprites() {
	// update sprites for everyhting
	// gameObjectContainer->screenManager->handlePlayerSprite(gameObjectContainer->player);
}

