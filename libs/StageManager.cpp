#pragma once

#include "StageManager.h"

StageManager::StageManager() = default;

StageManager::StageManager(std::unique_ptr<GameObjectContainer> gameObjectContainer) { // assign gameObjectContainer to each one of these managers
    screenManager = std::make_unique<ScreenManager>();
    collisionResolver = std::make_unique<CollisionResolver>(gameObjectContainer, screenManager.get());
    gameObjectFactory = std::make_unique<GameObjectFactory>(gameObjectContainer);
    keyboardManager = std::make_unique<KeyboardManager>(gameObjectContainer);

	// physics manager is entirely static
	// round manager doesnt exist yet
}

