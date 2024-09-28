#pragma once
#include "MovableGameObject.h"
#include <vector>

class BarrelContainer {
public:
    std::vector<MovableGameObject*> barrels;

    BarrelContainer() = default;

    void addBarrel(MovableGameObject* barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime) const;
    int getNumberOfElements() const;
};