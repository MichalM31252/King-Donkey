#pragma once

#include "MovableGameObject.h"
#include "BarrelHolder.h"
#include <memory>

class BarrelFactory {
public:
    int xpos;
    int ypos;
    double accumulatedTime;
    BarrelContainer* barrelContainer;

	explicit BarrelFactory(BarrelContainer* barrelContainer);

    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};
