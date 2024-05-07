#pragma once

extern "C" {
#include "DynamicGameObject.h"
}

class PhysicsManager {
public:
	static void handleFalling(DynamicGameObject* dynamicGameObject, double deltaTime);
};