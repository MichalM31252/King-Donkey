#pragma once

extern "C" {
#include "../GameObject.h"
}

class DynamicGameObject : public GameObject {
public:
	double accumulatedXMove, accumulatedYMove;
	bool canLeaveScreen;
	double gravity, objectSpeed;
	bool isFalling;
	double currentDirectionOfMovementHorizontal, currentDirectionOfMovementVertical;
	bool isClimbing, isInsideLadder;
	bool checkIfJumpPossible, isJumping;
	int jumpHeightStop;

	DynamicGameObject();
	void update(double deltaTime);
	void moveStart();
	void startMovingLeft(double delta);
	void startMovingRight(double delta);
	void startMovingUp(double delta);
	void startMovingDown(double delta);
	void stopMove();

	void initJump();
	void startJumping();
	void stopJumping();

	void startFalling();
	void stopFalling();
};