#pragma once

extern "C" {
#include "DynamicGameObject.h"
#include "ScreenManager.h"
}

class Barrel : public DynamicGameObject {
public:
	Barrel();
	void loadNextBarrelSprite();
};