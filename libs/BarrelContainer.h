#pragma once
#include "Barrel.h"
#include <vector>
#include <memory>

class BarrelContainer {
public:
    std::vector<std::shared_ptr<Barrel>> barrels;

    BarrelContainer() = default;

    void addBarrel(std::shared_ptr<Barrel> barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime) const;
    int getNumberOfElements() const;
};