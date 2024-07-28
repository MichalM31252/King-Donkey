#pragma once

extern "C" {
#include "MovableGameObject.h"
}

class PhysicsManager {
public:
	static void handleFalling(MovableGameObject* movableGameObject, double deltaTime);
};