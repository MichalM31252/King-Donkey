#pragma once

extern "C" {
#include "MovableGameObject.h"
#include "BarrelHolder.h"
}

class BarrelFactory {
private:
    int xpos, ypos;
    double accumulatedTime;
public:
    BarrelHolder* barrelHolder;

    void initBarrelFactory(BarrelFactory* barrelFactory);
    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};
