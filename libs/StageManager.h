#pragma once

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"

class StageManager {
private:
	CollisionManager* collisionManager;
	PhysicsManager* physicsManager;
	GameObjectFactory* gameObjectFactory;
};