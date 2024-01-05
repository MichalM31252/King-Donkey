#pragma once

extern "C" {
#include "../../Constants.h"
}

class Physics {
public:
	double gravity;
	bool isFalling;
	int currentDirectionOfMovement;

	Physics();
	void startFalling();
	void stopFalling();
};
