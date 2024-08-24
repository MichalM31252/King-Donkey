#pragma once

#include "GameObject.h"
#include "Constants.h"

class MovableGameObject : public GameObject {
public:
	double accumulatedMoveLeft;
	double accumulatedMoveUp;
	double accumulatedMoveRight;
	double accumulatedMoveDown;

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
	void startMovingLeft(double delta);
	void startMovingRight(double delta);
	void startMovingUp(double delta);
	void startMovingDown(double delta);
	void stopMove();

	void startFalling();
	void stopFalling();
};