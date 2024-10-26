#pragma once

#include "CollisionDetector.h"
#include "GameObjectContainer.h"

class PhysicsManager {
public:
	std::shared_ptr<GameObjectContainer> gameObjectContainer;

	explicit PhysicsManager(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handleFallingForPlayer(double deltaTime);
    void handleFallingForBarrels(double deltaTime);
	void forceFalling(MovableGameObject* gameObject, double deltaTime) const;
};