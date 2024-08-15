#pragma once

#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectFactory.h"

extern "C++" {
#include <memory>
}

class RoundManager {
public:
    std::unique_ptr<ScreenManager> screenManager;
    std::unique_ptr<GameObjectFactory> gameObjectFactory;
    std::unique_ptr<GameObjectContainer> gameObjectContainer;
    std::unique_ptr<CollisionResolver> collisionResolver;

    RoundManager();
    RoundManager(std::unique_ptr<ScreenManager> screenManager,
        std::unique_ptr<GameObjectFactory> gameObjectFactory,
        std::unique_ptr<GameObjectContainer> gameObjectContainer,
        std::unique_ptr<CollisionResolver> collisionResolver);

    void handleRound(int startAnotherRound);
    void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);
    void decideWhichBoardToCreate(int startAnotherRound);
};