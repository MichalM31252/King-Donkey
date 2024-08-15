#pragma once

#include "CollisionResolver.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"
#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectContainer.h"

extern "C++" {
#include <memory>
}

class StageManager {
private:
    std::unique_ptr<CollisionResolver> collisionResolver;
    std::unique_ptr<PhysicsManager> physicsManager;
    std::unique_ptr<GameObjectFactory> gameObjectFactory;
    std::unique_ptr<KeyboardManager> keyboardManager;
    std::unique_ptr<ScreenManager> screenManager;

	StageManager();
	StageManager(std::unique_ptr<GameObjectContainer> gameObjectContainer);
};