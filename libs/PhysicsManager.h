#pragma once

extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
}

class PhysicsManager {
public:
	// stop falling
	// start falling

	void handleFalling(DynamicGameObject* dynamicGameObject, double deltaTime);
};