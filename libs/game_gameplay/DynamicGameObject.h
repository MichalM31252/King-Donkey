#pragma once

extern "C" {
#include "../../libs/game_gameplay/GameObject.h"
}

class DynamicGameObject : public GameObject {
private:
	double objectSpeed;
public:
	void moveLeft(double delta);
	void moveRight(double delta);
	void moveUp(double delta);
	void moveDown(double delta);
	void moveStop();
};
