#include "Gorilla.h"

Gorilla::Gorilla(BarrelContainer* barrelContainer) {
	barrelFactory = new BarrelFactory(barrelContainer);
}

void Gorilla::update(double deltaTime) {
	barrelFactory->update(deltaTime);
}

