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
    std::shared_ptr<GameObjectContainer> gameObjectContainer;

    CollisionResolver();
    explicit CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handlePlayerCollisionWithKong() const;
    void handlePlayerCollisionWithPrincess() const;
    void handlePlayerCollisionWithBarrel(const MovableGameObject* barrel, bool* quit) const;
    void handleCollisionWithPlatform(MovableGameObject* gameObject);
    void handleCollisionWithJumping();

    void handlePlayerCollision();
    void handleBarrelsCollision(bool* quit);

    [[noreturn]] void closeGame() const;
};