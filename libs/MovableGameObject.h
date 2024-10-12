#pragma once

#include "GameObject.h"
#include "Constants.h"

enum CurrentDirectionOfMovementX {
	LEFT,
	RIGHT,
	NONE_X
};

enum CurrentDirectionOfMovementY {
	UP,
	DOWN,
	NONE_Y
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
	CurrentDirectionOfMovementX directionOfMovementX;
	CurrentDirectionOfMovementY directionOfMovementY;

	bool isFalling;
	double gravity;
	int currentSpriteId;

	MovableGameObject();
	void update(double deltaTime);
	virtual void startAccumulatingDistance(double deltaTime);
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