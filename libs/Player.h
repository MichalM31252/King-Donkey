#pragma once

extern "C" {
#include "MovableGameObject.h"
}

class Player : public MovableGameObject {
public:
	bool isInsideLadder;
	bool isJumping;

	Player();
	void jump(double deltaTime);
	void initJump();
	void startJumping();
	void stopJumping();

	void loadNextRunningSprite();
	void loadJumpingSprite();
	void loadClimbingSprite();
	void loadNextClimbingSprite();
	bool isPlayerJumping();
};