#pragma once

#include "MovableGameObject.h"
#include "ScreenManager.h"

class Barrel : public MovableGameObject {
public:
	Barrel();
	void loadNextSprite();
};