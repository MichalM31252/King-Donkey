#pragma once

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"
#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectContainer.h"

class StageManager {
private:
	CollisionManager* collisionManager;
	PhysicsManager* physicsManager;
	GameObjectFactory* gameObjectFactory;
	KeyboardManager* keyboardManager;
	ScreenManager* screenManager;

	StageManager();
	StageManager(GameObjectContainer *gameObjectContainer);
};