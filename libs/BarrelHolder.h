#pragma once
#include "MovableGameObject.h"
#include <vector>

class BarrelHolder {
public:
    std::vector<MovableGameObject*> barrels;

    BarrelHolder() = default;

    void addBarrel(MovableGameObject* barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime) const;
    int getNumberOfElements() const;
};