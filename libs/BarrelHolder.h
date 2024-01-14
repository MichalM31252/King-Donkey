#pragma once

extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
}

struct BarrelHolder {
	DynamicGameObject* barrels;
	int numberOfElements;
	int sizeOfArray;
};

void initBarrelHolder(BarrelHolder* barrelHolder);
void addBarrel(BarrelHolder* barrelHolder, DynamicGameObject* barrel);
void emptyBarrelHolder(BarrelHolder* barrelHolder);
