#pragma once
extern "C" {
#include "StageManager.h"
}

StageManager::StageManager() = default;

StageManager::StageManager(GameObjectContainer* gameObjectContainer) { // assign gameObjectContainer to each one of these managers
    screenManager = new ScreenManager();
    collisionResolver = new CollisionResolver(gameObjectContainer, screenManager);
    gameObjectFactory = new GameObjectFactory(gameObjectContainer);
    keyboardManager = new KeyboardManager(gameObjectContainer);

	// physics manager is entirely static
	// round manager doesnt exist yet
}

