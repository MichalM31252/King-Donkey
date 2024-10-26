#pragma once

#include <memory>
#include "GameObjectContainer.h"
#include "CollisionResolver.h"
#include "CollisionDetector.h"
#include "PhysicsManager.h"
#include "AnimationManager.h"

class GameObjectManager {
public:
	std::shared_ptr<GameObjectContainer> gameObjectContainer;
	CollisionResolver collisionResolver;
	CollisionDetector collisionDetector;
	PhysicsManager physicsManager;
	AnimationManager animationManager;
	
	GameObjectManager() = default;
	explicit GameObjectManager(std::shared_ptr<GameObjectContainer> gameObjectContainer);

	void updatePositionOfGameObjects(double deltaTime);
	void handleCollisionsOfGameObjects(bool& quit);
	void updateSpritesOfGameObjects();
	void updatePhysicsOfGameObjects(double deltaTime);
};