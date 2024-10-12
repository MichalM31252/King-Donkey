#pragma once
#include "MovableGameObject.h"

class Barrel : public MovableGameObject {
public:
	int currentSpriteId;
	int distanceTravelledFromLastSpriteChange;

	Barrel();
	void update(double deltaTime);
	void updatePosition();
	void loadNextSprite();
};