#pragma once

#include "BarrelFactory.h"
#include "BarrelHolder.h"

class Gorilla : public GameObject {
public:
	BarrelFactory* barrelFactory;

	Gorilla() = default;
	Gorilla(BarrelContainer* barrelContainer);

	void update(double deltaTime);

};