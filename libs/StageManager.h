#pragma once

#include "CollisionResolver.h"
#include "PhysicsManager.h"
#include "GameObjectFactory.h"
#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectContainer.h"

class StageManager {
private:
    CollisionResolver* collisionResolver;
    GameObjectFactory* gameObjectFactory;
    KeyboardManager* keyboardManager;
    ScreenManager* screenManager;

    StageManager() = default;
    // StageManager(GameObjectContainer* gameObjectContainer);
};