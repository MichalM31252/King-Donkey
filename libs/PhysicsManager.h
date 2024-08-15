#pragma once

extern "C" {
#include "Player.h"
#include "Barrel.h"
}

class PhysicsManager {
public:
	static void handleFallingForPlayer(std::unique_ptr<Player> player, double deltaTime);
	static void handleFalling(std::unique_ptr<MovableGameObject> gameObject, double deltaTime);
};