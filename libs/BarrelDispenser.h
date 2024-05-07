#pragma once

extern "C" {
#include "DynamicGameObject.h"
#include "BarrelHolder.h"
#include "BarrelDispenser.h"
#include "ScreenManager.h"
}

class BarrelDispenser {
public:
	int xpos, ypos;
	double deltaTime;
	double accumulatedTime;
	BarrelHolder* barrelHolder;

	void initBarrelDispenser(BarrelDispenser* barrelDispenser);
	void setPosition(int x, int y);
	void updateBarrelDispenser(double deltaTime);
	void throwBarrel();
};