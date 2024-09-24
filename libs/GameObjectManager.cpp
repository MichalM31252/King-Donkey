#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {
}

GameObjectManager::GameObjectManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer) 
	, collisionResolver(std::make_unique<CollisionResolver>(gameObjectContainer))
	, physicsManager(std::make_unique<PhysicsManager>(gameObjectContainer))
	// collision detector is completely stati2c
{
}

void GameObjectManager::updateGameObjects(double deltaTime) {
	gameObjectContainer->player->update(deltaTime);
	gameObjectContainer->barrelFactory->update(deltaTime);
	gameObjectContainer->barrelFactory->barrelHolder->updateBarrels(deltaTime);
}

void GameObjectManager::handleCollisions(bool& quit, int& startAnotherRound) {
	collisionResolver->handlePlayerCollision();
	collisionResolver->handleBarrelsCollision(&quit, &startAnotherRound);
}

void GameObjectManager::updateSprites() {
	
}

void GameObjectManager::updatePhysics(double deltaTime) {
	physicsManager->handleFallingForPlayer(gameObjectContainer->player, deltaTime);
	physicsManager->handleFallingForBarrels(gameObjectContainer->barrelFactory->barrelHolder, deltaTime);
}

