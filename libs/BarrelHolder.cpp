#include "BarrelHolder.h"

void BarrelContainer::addBarrel(MovableGameObject* barrel) {
    barrels.push_back(barrel);
}

void BarrelContainer::emptyBarrelHolder() {
    for (auto barrel : barrels) {
        delete barrel;
    }
    barrels.clear();
}

void BarrelContainer::updateBarrels(float deltaTime)  const{  
    for (auto barrel : barrels) {
        barrel->update(deltaTime);
    }
}

int BarrelContainer::getNumberOfElements() const {
    return barrels.size();
}