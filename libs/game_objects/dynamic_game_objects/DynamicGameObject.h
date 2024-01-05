#pragma once

extern "C" {
#include "../GameObject.h"
}

class DynamicGameObject : public GameObject {
public:
	bool canLeaveScreen;
	double gravity, objectSpeed;
	bool isFalling;
	int currentDirectionOfMovementHorizontal, currentDirectionOfMovementVertical;

	DynamicGameObject();
	void update(double deltaTime);
	void moveStart();
	void startMovingLeft(double delta);
	void startMovingRight(double delta);
	void startMovingUp(double delta);
	void startMovingDown(double delta);
	void moveStop();

	void startFalling();
	void stopFalling();
};