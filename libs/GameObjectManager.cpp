#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer) 
	, collisionResolver(std::make_unique<CollisionResolver>(gameObjectContainer))
	, physicsManager(std::make_unique<PhysicsManager>(gameObjectContainer))
	, animationManager(std::make_unique<AnimationManager>(gameObjectContainer))
{
}

void GameObjectManager::updatePositionOfGameObjects(double deltaTime) {
	gameObjectContainer->player->update(deltaTime);
	gameObjectContainer->barrelContainer->updateBarrels(deltaTime);
}

void GameObjectManager::handleCollisionsOfGameObjects(bool& quit) {
	collisionResolver->handlePlayerCollision();
	collisionResolver->handleBarrelsCollision(&quit);
}

void GameObjectManager::updateSpritesOfGameObjects(double deltaTime) {
	animationManager->handleAnimations(deltaTime);
}

void GameObjectManager::updatePhysicsOfGameObjects(double deltaTime) {
	physicsManager->handleFallingForPlayer(deltaTime);
	physicsManager->handleFallingForBarrels(deltaTime);
}

