#pragma once

#include "BarrelFactory.h"
#include "BarrelHolder.h"

class Gorilla : public GameObject {
public:
	BarrelFactory* barrelFactory;

	Gorilla();
	Gorilla(BarrelHolder* barrelHolder);

	void update(double deltaTime);

};