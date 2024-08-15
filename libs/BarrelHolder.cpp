extern "C" {
#include "BarrelHolder.h"
}

void BarrelHolder::addBarrel(std::unique_ptr<MovableGameObject> barrel) {
    barrels.push_back(std::move(barrel));
}

void BarrelHolder::emptyBarrelHolder() {
    barrels.clear();
}

void BarrelHolder::updateBarrels(float deltaTime) {
    for (auto& barrel : barrels) {
        barrel->update(deltaTime);
    }
}

int BarrelHolder::getNumberOfElements(){
	return barrels.size();
}