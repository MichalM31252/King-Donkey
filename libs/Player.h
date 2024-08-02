#pragma once

extern "C" {
#include "MovableGameObject.h"
}

class Player : public MovableGameObject {
public:
	bool isInsideLadder;
	bool isJumping;
	bool isClimbing;

	Player();
	void jump(double deltaTime);
	void initJump();
	void startJumping();
	void stopJumping();
	void startClimbing();
	void stopClimbing();

	void loadNextRunningSprite();
	void loadJumpingSprite();
	void loadClimbingSprite();
	void loadNextClimbingSprite();
	bool isPlayerJumping();

	void startAccumulatingDistance(double deltaTime) override;
};