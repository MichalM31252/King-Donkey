#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(std::shared_ptr<GameObjectContainer> gameObjectContainer)
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

void GameObjectManager::handleCollisionsOfGameObjects(GameState* gameState) {
	collisionResolver.handlePlayerCollision();
	collisionResolver.handleBarrelsCollision(gameState);
}

void GameObjectManager::updateSpritesOfGameObjects() {
	animationManager.handleAnimations();
}

void GameObjectManager::updatePhysicsOfGameObjects(double deltaTime) {
	physicsManager.handleFallingForPlayer(deltaTime);
	physicsManager.handleFallingForBarrels(deltaTime);
}

