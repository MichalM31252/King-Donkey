#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Platform.h"
#include "GameObject.h"
#include "MovableGameObject.h"
#include "GameObjectContainer.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"
#include "CollisionDetector.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class CollisionResolver {
public:
    GameObjectContainer* gameObjectContainer;

    CollisionResolver();
    explicit CollisionResolver(GameObjectContainer* gameObjectContainer);

    void handlePlayerCollisionWithKong() const;
    void handlePlayerCollisionWithPrincess() const;
    void handlePlayerCollisionWithBarrel(const MovableGameObject* barrel, bool* quit, int* startAnotherRound) const;
    void handlePlayerCollisionWithLadder();
    void handleCollisionWithPlatform(MovableGameObject* gameObject);
    void handleCollisionWithJumping();

    void handlePlayerCollision();
    void handleBarrelsCollision(bool* quit, int* startAnotherRound);

    [[noreturn]] void closeGame() const;
};