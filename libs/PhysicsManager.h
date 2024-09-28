#pragma once
#include "Player.h"
#include "Barrel.h"
#include "BarrelHolder.h"
#include "CollisionDetector.h"

class PhysicsManager {
public:
	GameObjectContainer* gameObjectContainer;

	explicit PhysicsManager(GameObjectContainer* gameObjectContainer);

    void handleFallingForPlayer(double deltaTime);
    void handleFallingForBarrels(double deltaTime);
	void startFalling(MovableGameObject* gameObject, double deltaTime) const;
};