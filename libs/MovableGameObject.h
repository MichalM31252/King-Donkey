#pragma once

#include "GameObject.h"
#include "Constants.h"

enum class DirectionX {
	NONE = 0,
	LEFT,
	RIGHT
};

enum class DirectionY {
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
	DirectionX currentDirectionOfMovementX;
	DirectionY currentDirectionOfMovementY;

	bool isFalling;
	double gravity;

	MovableGameObject();
	void update(double deltaTime);
	virtual void accumulateDistance(double deltaTime);
	void updatePositionCoordinates();

	void stayInBounds();
	void updatePosition();
	void startMovingHorizontallyAtSpeed(double speed);
	void startMovingVerticallyAtSpeed(double speed);
	void startMovingRight();
	void startMovingLeft();
	void startMovingUp();
	void startMovingDown();
	void stopMove();

	void startFalling();
	void stopFalling();
};