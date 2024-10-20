#pragma once

#include "GameObject.h"
#include "Constants.h"

enum class CurrentDirectionOfMovementX {
	NONE = 0,
	LEFT,
	RIGHT
};

enum class CurrentDirectionOfMovementY {
	NONE = 0,
	UP,
	DOWN
};

class MovableGameObject : public GameObject {
public:
	double accumulatedMoveUp;
	double accumulatedMoveRight;
	double accumulatedMoveDown;
	double accumulatedMoveLeft;

	bool canLeaveScreen;

	unsigned int velocityX;
	unsigned int velocityY;
	CurrentDirectionOfMovementX currentDirectionOfMovementX;
	CurrentDirectionOfMovementY currentDirectionOfMovementY;

	bool isFalling;
	double gravity;
	int currentSpriteId;

	MovableGameObject();
	void update(double deltaTime);
	virtual void accumulateDistance(double deltaTime);
	void updatePositionCoordinates();

	void stayInBounds();
	void updatePosition();
	void startMovingHorizontallyAtSpeed(double speed);
	void startMovingVerticallyAtSpeed(double speed);
	void startMovingRight();
	void startMovingUp();
	void startMovingDown();
	void stopMove();

	void startFalling();
	void stopFalling();
};