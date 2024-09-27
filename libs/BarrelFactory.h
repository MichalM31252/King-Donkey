#pragma once

#include "MovableGameObject.h"
#include "BarrelHolder.h"

class BarrelFactory {
public:
    int xpos;
    int ypos;
    double accumulatedTime;
    BarrelContainer* barrelHolder;

	BarrelFactory() = default;
	explicit BarrelFactory(BarrelContainer* barrelHolder);

    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};
