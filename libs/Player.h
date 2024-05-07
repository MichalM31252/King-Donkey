#pragma once

extern "C" {
#include "DynamicGameObject.h"
#include "ScreenManager.h"
}

class Player : public DynamicGameObject {
public:
	Player();
	void jump(double deltaTime);
};