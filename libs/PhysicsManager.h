#pragma once

extern "C" {
#include "Player.h"
#include "Barrel.h"
}

class PhysicsManager {
public:
	static void handleFallingForPlayer(Player* player, double deltaTime);
	static void handleFalling(MovableGameObject* object, double deltaTime);
};