#pragma once

#include "MovableGameObject.h"

class Player : public MovableGameObject {
public:
	bool isInsideLadder;
	bool isJumping;
	int distanceTravelledFromLastRunningSprite;
	bool isClimbing;
	bool checkIfJumpPossible;
	int jumpHeightStop;

	int currentClimbingSpriteId;
	int currentRunningSpriteId;

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
	void loadIdleSprite();
	bool isPlayerMovingVertically() const;
	bool isPlayerJumping() const;

	void update(double deltaTime);
	void updatePosition();

	void startAccumulatingDistance(double deltaTime) override;
};