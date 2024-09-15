#pragma once

#include <memory>
#include "CollisionResolver.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"
#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectContainer.h"

class StageManager {
public:
    std::unique_ptr<CollisionResolver> collisionResolver;
    std::unique_ptr<GameObjectFactory> gameObjectFactory;
    std::unique_ptr<KeyboardManager> keyboardManager;
    std::unique_ptr<ScreenManager> screenManager;

    StageManager() = default;
    // StageManager(GameObjectContainer* gameObjectContainer);
};