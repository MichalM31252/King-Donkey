#pragma once

extern "C" {
#include "MovableGameObject.h"
#include "BarrelHolder.h"
}

extern "C++" {
#include <memory>
}

class BarrelFactory {
private:
    int xpos, ypos;
    double accumulatedTime;
public:
    std::unique_ptr<BarrelHolder> barrelHolder;

    void initBarrelFactory(BarrelFactory* barrelFactory) const;
    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};