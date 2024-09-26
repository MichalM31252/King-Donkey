#include "Gorilla.h"

Gorilla::Gorilla() {
	barrelFactory = new BarrelFactory();
}

Gorilla::Gorilla(BarrelHolder* barrelHolder) {
	barrelFactory = new BarrelFactory(barrelHolder);
}

void Gorilla::update(double deltaTime) {
	barrelFactory->update(deltaTime);
}

