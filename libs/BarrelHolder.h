#pragma once

extern "C" {
#include "MovableGameObject.h"
}

extern "C++" {
#include <memory>
#include <vector>
}

class BarrelHolder {
public:
    std::vector<std::unique_ptr<MovableGameObject>> barrels;
    
    BarrelHolder() = default;

    void addBarrel(std::unique_ptr<MovableGameObject> barrel);
    void emptyBarrelHolder();
    void updateBarrels(float deltaTime);
    int getNumberOfElements();
};
