#pragma once

#include <memory>
#include "BarrelFactory.h"
#include "BarrelContainer.h"

class Gorilla : public GameObject {
public:
	BarrelFactory barrelFactory;

	Gorilla() = default;
	explicit Gorilla(std::shared_ptr<BarrelContainer> barrelContainer);

	void update(double deltaTime);
};