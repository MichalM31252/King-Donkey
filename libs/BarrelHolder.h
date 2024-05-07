#pragma once

extern "C" {
#include "DynamicGameObject.h"
}

struct BarrelHolder {
	DynamicGameObject* barrels;
	int numberOfElements;
	int sizeOfArray;
};

void initBarrelHolder(BarrelHolder* barrelHolder);
void addBarrel(BarrelHolder* barrelHolder, DynamicGameObject* barrel);
void emptyBarrelHolder(BarrelHolder* barrelHolder);
