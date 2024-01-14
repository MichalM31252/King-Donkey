extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "./BarrelHolder.h"
}

void initBarrelHolder(BarrelHolder* barrelHolder) {
	barrelHolder->barrels = new DynamicGameObject[MAXIMUM_AMOUNT_OF_BARRELS]; // this is the reason why platforms are not pointers
	barrelHolder->numberOfElements = 0; // number of elements currently inside
	barrelHolder->sizeOfArray = MAXIMUM_AMOUNT_OF_BARRELS;
}

void addBarrel(BarrelHolder* barrelHolder, DynamicGameObject* barrel) { // this doesn't work
	if (barrelHolder->numberOfElements == barrelHolder->sizeOfArray) {
		DynamicGameObject* temp = new DynamicGameObject[barrelHolder->sizeOfArray];

		for (int i = 0; i < barrelHolder->numberOfElements; i++) {
			temp[i] = barrelHolder->barrels[i];
		}

		delete[] barrelHolder->barrels;

		barrelHolder->barrels = temp;
		barrelHolder->sizeOfArray *= 2;
	}
	barrelHolder->barrels[barrelHolder->numberOfElements] = *barrel;
	barrelHolder->numberOfElements++;
}

void emptyBarrelHolder(BarrelHolder* barrelHolder) {
	delete[] barrelHolder->barrels;
}