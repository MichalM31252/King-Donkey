#include "BarrelContainer.h"

void BarrelContainer::addBarrel(std::shared_ptr<Barrel> barrel) {
    barrels.push_back(barrel);
}

void BarrelContainer::emptyBarrelHolder() {
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