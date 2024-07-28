#pragma once

extern "C" {
#include "MovableGameObject.h"
}

class Player : public MovableGameObject {
public:
	bool isInsideLadder;

	Player();
	void jump(double deltaTime);
	void initJump();
	void startJumping();
	void stopJumping();

	void loadNextRunningSprite();
	void loadJumpingSprite();
	void loadClimbingSprite();
	void loadNextClimbingSprite();
};