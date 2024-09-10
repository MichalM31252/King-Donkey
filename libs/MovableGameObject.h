#pragma once

#include "GameObject.h"
#include "Constants.h"

class MovableGameObject : public GameObject {
public:
	double accumulatedMoveUp;
	double accumulatedMoveRight;
	double accumulatedMoveDown;
	double accumulatedMoveLeft;

	bool canLeaveScreen;
	double objectSpeed;
	bool isFalling;
	double gravity;
	int currentDirectionOfMovement;
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