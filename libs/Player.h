#pragma once

#include "MovableGameObject.h"

class Player : public MovableGameObject {
public:
	bool isJumping;
	int distanceTravelledFromLastRunningSprite;
	int distanceTravelledFromLastClimbingSprite;
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

	void loadNextRightRunningSprite();
	void loadNextLeftRunningSprite();

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