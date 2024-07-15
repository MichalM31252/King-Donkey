#pragma once

extern "C" {
#include "DynamicGameObject.h"
}

class Player : public DynamicGameObject {
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
};