#pragma once

#include "CollisionDetector.h"
#include "GameObjectContainer.h"

class PhysicsManager {
public:
	GameObjectContainer* gameObjectContainer;

	explicit PhysicsManager(GameObjectContainer* gameObjectContainer);

    void handleFallingForPlayer(double deltaTime);
    void handleFallingForBarrels(double deltaTime);
	void forceFalling(MovableGameObject* gameObject, double deltaTime) const;
};