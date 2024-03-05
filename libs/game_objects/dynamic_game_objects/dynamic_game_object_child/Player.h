#pragma once

extern "C" {
#include "../DynamicGameObject.h"
}

class Player : public DynamicGameObject {
public:
	Player();
	void jump();
};