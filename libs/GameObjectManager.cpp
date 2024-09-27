#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer) 
	, collisionResolver(std::make_unique<CollisionResolver>(gameObjectContainer))
	, physicsManager(std::make_unique<PhysicsManager>(gameObjectContainer))
	// collision detector is completely stati2c
{
}

void GameObjectManager::updateGameObjects(double deltaTime) {
	gameObjectContainer->player->update(deltaTime);
	gameObjectContainer->donkeyKong->update(deltaTime);
	gameObjectContainer->barrelContainer->updateBarrels(deltaTime);
}

void GameObjectManager::handleCollisionsOfGameObjects(bool& quit, int& startAnotherRound) {
	collisionResolver->handlePlayerCollision();
	collisionResolver->handleBarrelsCollision(&quit, &startAnotherRound);
}

void GameObjectManager::updateSpritesOfGameObjects() {
	
}

void GameObjectManager::updatePhysicsOfGameObjects(double deltaTime) {
	physicsManager->handleFallingForPlayer(deltaTime);
	physicsManager->handleFallingForBarrels(deltaTime);
}

