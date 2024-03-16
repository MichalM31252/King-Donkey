#pragma once

extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
}

class PhysicsManager {
public:
	void handleFalling(DynamicGameObject* dynamicGameObject, double deltaTime);
};