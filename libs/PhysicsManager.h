#pragma once
#include "Player.h"
#include "Barrel.h"

class PhysicsManager {
public:
    static void handleFallingForPlayer(Player* player, double deltaTime);
    static void handleFalling(MovableGameObject* gameObject, double deltaTime);
};