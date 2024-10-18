#pragma once

#include "GameObjectContainer.h"

class AnimationManager {
public:
	GameObjectContainer* gameObjectContainer;

	AnimationManager() = default;
	explicit AnimationManager(GameObjectContainer* gameObjectContainer);

	void handleAnimations();

	void handlePlayerAnimation();
	void handleAllBarrelsAnimation() const;
};
