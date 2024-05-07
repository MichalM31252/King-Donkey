extern "C" {
#include "BarrelHolder.h"
}

void initBarrelHolder(BarrelHolder* barrelHolder) {
	barrelHolder->barrels = new DynamicGameObject[MAXIMUM_AMOUNT_OF_BARRELS];
	barrelHolder->numberOfElements = 0;
	barrelHolder->sizeOfArray = MAXIMUM_AMOUNT_OF_BARRELS;
}

void addBarrel(BarrelHolder* barrelHolder, DynamicGameObject* barrel) {
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