#pragma once
#include "Player.h"
#include "Barrel.h"
#include "BarrelHolder.h"
#include "CollisionDetector.h"

class PhysicsManager {
public:
	GameObjectContainer* gameObjectContainer;

	explicit PhysicsManager(GameObjectContainer* gameObjectContainer);

    void handleFallingForPlayer(Player* player, double deltaTime);
    void handleFallingForBarrels(BarrelHolder* barrelHolder, double deltaTime);
	void startFalling(MovableGameObject* gameObject, double deltaTime) const;
};