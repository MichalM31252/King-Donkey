#pragma once

extern "C" {
#include "MovableGameObject.h"
}

extern "C++" {
#include <memory>
}

struct BarrelHolder {
    std::unique_ptr<MovableGameObject[]> barrels;
    int numberOfElements;
    int sizeOfArray;
};

void initBarrelHolder(std::unique_ptr<BarrelHolder> barrelHolder);
void addBarrel(std::unique_ptr<BarrelHolder> barrelHolder, std::unique_ptr<MovableGameObject> barrel);
void emptyBarrelHolder(std::unique_ptr<BarrelHolder> barrelHolder);
void updateBarrels(std::unique_ptr<BarrelHolder> barrelHolder, float deltaTime);
