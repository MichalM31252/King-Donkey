#pragma once

extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "./BarrelHolder.h"
#include "./BarrelDispenser.h"
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