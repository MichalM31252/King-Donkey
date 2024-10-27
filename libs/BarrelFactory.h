#pragma once

#include "MovableGameObject.h"
#include "BarrelContainer.h"
#include <memory>

class BarrelFactory {
public:
    int xpos;
    int ypos;
    double accumulatedTime;
    std::shared_ptr<BarrelContainer> barrelContainer;

	explicit BarrelFactory(std::shared_ptr<BarrelContainer> barrelContainer);

    void setPosition(int x, int y);
    void update(double deltaTime);
    void throwBarrel();
};
