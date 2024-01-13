#pragma once

extern "C" {
#include "../DynamicGameObject.h"
}

class Player : public DynamicGameObject {
public:
	bool isClimbing;
	Player();
	void jump();
};