#pragma once

#include "MovableGameObject.h"
#include "BarrelHolder.h"

class BarrelFactory {
public:
    int xpos;
    int ypos;
    double accumulatedTime;
    BarrelHolder* barrelHolder;

	BarrelFactory() = default;
	explicit BarrelFactory(BarrelHolder* barrelHolder);

    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};
