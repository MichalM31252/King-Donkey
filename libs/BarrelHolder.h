#pragma once

extern "C" {
#include "MovableGameObject.h"
}

struct BarrelHolder {
	MovableGameObject* barrels;
	int numberOfElements;
	int sizeOfArray;
};

void initBarrelHolder(BarrelHolder* barrelHolder);
void addBarrel(BarrelHolder* barrelHolder, MovableGameObject* barrel);
void emptyBarrelHolder(BarrelHolder* barrelHolder);
