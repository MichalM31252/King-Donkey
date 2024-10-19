#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(GameObjectContainer* gameObjectContainer)
	: gameObjectContainer(gameObjectContainer) 
	, collisionResolver(CollisionResolver(gameObjectContainer))
	, physicsManager(PhysicsManager(gameObjectContainer))
	, animationManager(AnimationManager(gameObjectContainer))
{
}

void GameObjectManager::updatePositionOfGameObjects(double deltaTime) {
	gameObjectContainer->player->update(deltaTime);
	gameObjectContainer->barrelContainer->updateBarrels(deltaTime);
}

void GameObjectManager::handleCollisionsOfGameObjects(bool& quit) {
	collisionResolver.handlePlayerCollision();
	collisionResolver.handleBarrelsCollision(&quit);
}

void GameObjectManager::updateSpritesOfGameObjects(double deltaTime) {
	animationManager.handleAnimations();
}

void GameObjectManager::updatePhysicsOfGameObjects(double deltaTime) {
	physicsManager.handleFallingForPlayer(deltaTime);
	physicsManager.handleFallingForBarrels(deltaTime);
}

