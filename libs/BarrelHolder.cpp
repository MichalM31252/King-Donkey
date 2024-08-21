#include "BarrelHolder.h"

void BarrelHolder::addBarrel(MovableGameObject* barrel) {
    barrels.push_back(barrel);
}

void BarrelHolder::emptyBarrelHolder() {
    for (auto barrel : barrels) {
        delete barrel;
    }
    barrels.clear();
}

void BarrelHolder::updateBarrels(float deltaTime) {  
    for (auto barrel : barrels) {
        barrel->update(deltaTime);
    }
}

int BarrelHolder::getNumberOfElements() {
    return static_cast<int>(barrels.size());
}