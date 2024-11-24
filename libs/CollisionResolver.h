#pragma once
#include "MovableGameObject.h"
#include "GameObjectContainer.h"
#include "GameTime.h"
#include "GameState.h"


class CollisionResolver {
public:
    std::shared_ptr<GameObjectContainer> gameObjectContainer;

    CollisionResolver();
    explicit CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handlePlayerCollisionWithKong() const;
    void handlePlayerCollisionWithPrincess() const;
    void handlePlayerCollisionWithBarrel(std::shared_ptr<Barrel> barrel, GameState* gameState) const;
    void handleCollisionWithPlatform(const std::shared_ptr<MovableGameObject>& gameObject);
    void handleCollisionWithJumping();

    void handlePlayerCollision();
    void handleBarrelsCollision(GameState* gameState);

    [[noreturn]] void closeGame() const;
};