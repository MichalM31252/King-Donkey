#include "Gorilla.h"

Gorilla::Gorilla(std::shared_ptr<BarrelContainer> barrelContainer)
	: barrelFactory(barrelContainer)
{
}

void Gorilla::update(double deltaTime) {
	barrelFactory.update(deltaTime);
}

