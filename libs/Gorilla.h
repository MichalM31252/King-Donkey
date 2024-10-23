#pragma once

#include <memory>
#include "BarrelFactory.h"
#include "BarrelHolder.h"

class Gorilla : public GameObject {
public:
	BarrelFactory barrelFactory;

	Gorilla() = default;
	explicit Gorilla(BarrelContainer* barrelContainer);

	void update(double deltaTime);
};