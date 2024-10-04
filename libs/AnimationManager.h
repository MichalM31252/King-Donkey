#pragma once

#include "GameObjectContainer.h"

class AnimationManager {
public:
	GameObjectContainer* gameObjectContainer;

	AnimationManager() = default;
	AnimationManager(GameObjectContainer* gameObjectContainer);

	void handleAnimations(double deltaTime);

	void handlePlayerAnimation();
	void handleBarrelAnimation();
	void handleGorillaAnimation(double deltaTime);
};
