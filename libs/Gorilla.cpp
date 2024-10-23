#include "Gorilla.h"

Gorilla::Gorilla(BarrelContainer* barrelContainer) 
	: barrelFactory(barrelContainer) 
{
}

void Gorilla::update(double deltaTime) {
	barrelFactory.update(deltaTime);
}

