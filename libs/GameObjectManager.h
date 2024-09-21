#pragma once

#include <memory>
#include "GameObjectContainer.h"
#include "CollisionResolver.h"
#include "CollisionDetector.h"
#include "PhysicsManager.h"

class GameObjectManager {
public:
	std::unique_ptr<GameObjectContainer> gameObjectContainer;
	std::unique_ptr<CollisionResolver> collisionResolver;
	std::unique_ptr<CollisionDetector> collisionDetector;
	std::unique_ptr<PhysicsManager> physicsManager;

	GameObjectManager();
	GameObjectManager(GameObjectContainer* gameObjectContainer);

	void updateGameObjects(double deltaTime);
	void handleCollisions(bool& quit, int& startAnotherRound);
	void updateSprites();
};