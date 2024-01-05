#pragma once

extern "C" {
#include "../GameObject.h"
}

class DynamicGameObject : public GameObject {
public:
	bool canLeaveScreen;
	double gravity, objectSpeed;
	bool isFalling;
	int currentDirectionOfMovement;

	DynamicGameObject();
	void moveStart();
	void moveLeft(double delta);
	void moveRight(double delta);
	void moveUp(double delta);
	void moveDown(double delta);
	void moveStop();

	void startFalling();
	void stopFalling();
};