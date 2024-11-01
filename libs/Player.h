#pragma once

#include "MovableGameObject.h"
#include "CollisionDetector.h"

class Player : public MovableGameObject {
public:
	// State flags
	bool isJumping;
	bool isClimbing;

	// Animation tracking
	int currentRunningSpriteId;
	int currentClimbingSpriteId;

	// Distance tracking
	int distanceTravelledFromLastRunningSprite;
	int distanceTravelledFromLastClimbingSprite;

	// Jumping mechanics
	int jumpHeightStop;
	bool checkIfJumpPossible;

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

	bool isMovingVertically() const;

	void update(double deltaTime);
	void updatePosition();
	void accumulateDistance(double deltaTime) override;

	// handle animations based on direction method 
};