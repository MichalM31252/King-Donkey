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

	bool isPlayer;
	int currentRunningSpriteId;
	int currentRunningSpriteIdBarrel;
	void decideSpritePlayer();
	void decideSpriteBarrel();

	DynamicGameObject();
	void update(double deltaTime);

	void stayInBounds();
	void updatePosition();
	void startAccumulatingDistance(double deltaTime);

	void moveStart(double speed);
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