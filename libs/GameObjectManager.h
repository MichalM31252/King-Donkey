#pragma once

#include <memory>
#include "GameObjectContainer.h"
#include "CollisionResolver.h"
#include "CollisionDetector.h"
#include "PhysicsManager.h"
#include "AnimationManager.h"

class GameObjectManager {
public:
	std::unique_ptr<GameObjectContainer> gameObjectContainer;
	std::unique_ptr<CollisionResolver> collisionResolver;
	std::unique_ptr<CollisionDetector> collisionDetector;
	std::unique_ptr<PhysicsManager> physicsManager;
	std::unique_ptr<AnimationManager> animationManager;
	
	GameObjectManager() = default;
	explicit GameObjectManager(GameObjectContainer* gameObjectContainer);

	void updatePositionOfGameObjects(double deltaTime);
	void handleCollisionsOfGameObjects(bool& quit);
	void updateSpritesOfGameObjects(double deltaTime);
	void updatePhysicsOfGameObjects(double deltaTime);
};