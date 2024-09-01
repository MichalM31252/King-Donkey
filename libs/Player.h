#pragma once

#include "MovableGameObject.h"

class Player : public MovableGameObject {
public:
	bool isInsideLadder;
	bool isJumping;
	bool isClimbing;
	bool checkIfJumpPossible;
	int jumpHeightStop;

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
	bool isPlayerMovingVertically() const;
	bool isPlayerJumping() const;

	void startAccumulatingDistance(double deltaTime) override;
};