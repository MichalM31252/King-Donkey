#pragma once

extern "C" {
#include "GameObject.h"
#include "Constants.h"
}

class MovableGameObject : public GameObject {
public:
	double accumulatedMoveLeft, accumulatedMoveUp, accumulatedMoveRight, accumulatedMoveDown;
	bool canLeaveScreen;
	double objectSpeed;

	bool isFalling;
	double gravity;

	int currentDirectionOfMovement;

	bool isClimbing;
	bool checkIfJumpPossible, isJumping;
	int jumpHeightStop;

	bool isPlayer;

	int currentSpriteId;

	MovableGameObject();
	void update(double deltaTime);

	// move this to gameObjectsManager
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void stayInBounds();
	void updatePosition();
	void startAccumulatingDistance(double deltaTime);
	void startMovingAtSpeed(double speed);
	void startMovingLeft(double delta);
	void startMovingRight(double delta);
	void startMovingUp(double delta);
	void startMovingDown(double delta);
	void stopMove();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// move this to physcics manager
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void startFalling();
	void stopFalling();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
};