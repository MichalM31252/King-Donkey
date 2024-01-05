#pragma once

extern "C" {
#include "../../libs/game_gameplay/GameObject.h"
#include "../../libs/game_gameplay/Physics.h"
}

class DynamicGameObject : public GameObject {
public:
	double objectSpeed;
	Physics physics;
	void moveStart();
	void moveLeft(double delta);
	void moveRight(double delta);
	void moveUp(double delta);
	void moveDown(double delta);
	void moveStop();
};
