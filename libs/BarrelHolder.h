#pragma once
#include "Barrel.h"
#include <vector>

class BarrelContainer {
public:
    std::vector<Barrel*> barrels; // this should be barrel class

    BarrelContainer() = default;

    void addBarrel(Barrel* barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime) const;
    int getNumberOfElements() const;
};