#include "Gorilla.h"

Gorilla::Gorilla() {
	barrelFactory = new BarrelFactory();
}

Gorilla::Gorilla(BarrelContainer* barrelHolder) {
	barrelFactory = new BarrelFactory(barrelHolder);
}

void Gorilla::update(double deltaTime) {
	barrelFactory->update(deltaTime);
}

