#pragma once

#include "CollisionDetector.h"
#include "GameObjectContainer.h"

class PhysicsManager {
public:
	std::shared_ptr<GameObjectContainer> gameObjectContainer;

	explicit PhysicsManager(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handleFallingForPlayer(double deltaTime);
    void handleFallingForBarrels(double deltaTime);
	void forceFalling(std::shared_ptr<MovableGameObject> movableGameObject, double deltaTime) const;
};