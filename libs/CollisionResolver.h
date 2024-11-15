#pragma once
#include "MovableGameObject.h"
#include "GameObjectContainer.h"


class CollisionResolver {
public:
    std::shared_ptr<GameObjectContainer> gameObjectContainer;

    CollisionResolver();
    explicit CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handlePlayerCollisionWithKong() const;
    void handlePlayerCollisionWithPrincess() const;
    void handlePlayerCollisionWithBarrel(std::shared_ptr<Barrel> barrel, bool* quit) const;
    void handleCollisionWithPlatform(const std::shared_ptr<MovableGameObject>& gameObject);
    void handleCollisionWithJumping();

    void handlePlayerCollision();
    void handleBarrelsCollision(bool* quit);

    [[noreturn]] void closeGame() const;
};