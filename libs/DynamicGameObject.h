#pragma once

extern "C" {
#include "../GameObject.h"
#include "../../Constants.h"
#include "../../game_screen/ScreenManager.h"
}

class DynamicGameObject : public GameObject {
public:
	double accumulatedXMove, accumulatedYMove;
	bool canLeaveScreen;
	double objectSpeed;

	bool isFalling;
	double gravity;
	
	double currentDirectionOfMovementHorizontal, currentDirectionOfMovementVertical;
	bool isClimbing, isInsideLadder;
	bool checkIfJumpPossible, isJumping;
	int jumpHeightStop;

	bool isPlayer;
	int currentRunningSpriteId;
	int currentRunningSpriteIdBarrel;

	// this should be in a different class
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	void decideSpritePlayer();
	void decideSpriteBarrel();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	DynamicGameObject();
	void update(double deltaTime);

	// move this to gameObjectsManager
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// move this to physcics manager
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void startFalling();
	void stopFalling();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
};