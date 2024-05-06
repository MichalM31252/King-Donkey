#pragma once

#include "./game_events/CollisionManager.h"
#include "./PhysicsManager.h"
#include "./GameObjectFactory.h"
#include "./GameObjectVisualiser.h"

class StageManager {
private:
	CollisionManager* collisionManager;
	PhysicsManager* physicsManager;
	GameObjectFactory* gameObjectFactory;
};