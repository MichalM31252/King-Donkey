#pragma once

extern "C" {
#include "DynamicGameObject.h"
#include "BarrelHolder.h"
#include "BarrelDispenser.h"
}

class BarrelDispenser {
private:
	int xpos, ypos;
	double accumulatedTime;
public:
	BarrelHolder* barrelHolder;

	void initBarrelDispenser(BarrelDispenser* barrelDispenser);
	void setPosition(int x, int y);
	void updateBarrelDispenser(double deltaTime);
	void throwBarrel();
};