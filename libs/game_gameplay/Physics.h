#pragma once

extern "C" {
#include "../Constants.h"
#include "../../libs/game_gameplay/DynamicGameObject.h"
}

class Physics {
	double gravity;
	bool isFalling;
	int currentDirectionOfMovement;
	void startFalling(DynamicGameObject* object);
	void stopFalling(DynamicGameObject* object);
};
