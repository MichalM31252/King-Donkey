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

    void initBarrelFactory(std::unique_ptr<BarrelFactory> barrelFactory);
    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};