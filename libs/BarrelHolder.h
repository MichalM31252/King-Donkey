#pragma once

extern "C" {
#include "MovableGameObject.h"
}

extern "C++" {
#include <vector>
}

class BarrelHolder {
public:
    std::vector<MovableGameObject*> barrels;

    BarrelHolder() = default;

    void addBarrel(MovableGameObject* barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime);
    int getNumberOfElements();
};