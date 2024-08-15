#pragma once
extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

#include "Platform.h"
#include "GameObject.h"
#include "MovableGameObject.h"
#include "GameObjectContainer.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"
#include "CollisionDetector.h"
}

extern "C++" {
#include <memory>
}

// Does something when objects collide

class CollisionResolver {
public:
    std::unique_ptr<GameObjectContainer> gameObjectContainer;
    std::unique_ptr<ScreenManager> screenManager;

    CollisionResolver();
    CollisionResolver(std::unique_ptr<GameObjectContainer> gameObjectContainer, std::unique_ptr<ScreenManager> screenManager);

    void handlePlayerCollisionWithKong();
    void handlePlayerCollisionWithPrincess();
    void handlePlayerCollisionWithBarrel(std::unique_ptr<MovableGameObject> barrel, bool* quit, int* startAnotherRound);
    void handlePlayerCollisionWithLadder();
    void handleCollisionWithPlatform(std::unique_ptr<MovableGameObject> gameObject);
    void handleCollisionWithJumping();

    void handlePlayerCollision();
    void handleBarrelsCollision(bool* quit, int* startAnotherRound);

    void closeGame();
};