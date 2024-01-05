#pragma once

extern "C" {
#include "../GameObject.h"
#include "./Physics.h"
}

class DynamicGameObject : public GameObject {
public:
	double objectSpeed;
	Physics physics;
	DynamicGameObject();
	void moveStart();
	void moveLeft(double delta);
	void moveRight(double delta);
	void moveUp(double delta);
	void moveDown(double delta);
	void moveStop();
};
