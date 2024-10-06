#pragma once

#include "GameObject.h"
#include "Constants.h"

enum DirectionOfMovementX {
	LEFT,
	RIGHT,
	NONE
};

enum DirectionOfMovementY {
	UP,
	DOWN,
	NONE
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
	DirectionOfMovementX directionOfMovementX;
	DirectionOfMovementY directionOfMovementY;

	bool isFalling;
	double gravity;
	int currentSpriteId;

	MovableGameObject();
	void update(double deltaTime);
	virtual void startAccumulatingDistance(double deltaTime);
	void updatePositionCoordinates();

	void stayInBounds();
	void updatePosition();
	void startMovingAtSpeed(double speed);
	void startMovingLeft();
	void startMovingRight();
	void startMovingUp();
	void startMovingDown();
	void stopMove();

	void startFalling();
	void stopFalling();
};