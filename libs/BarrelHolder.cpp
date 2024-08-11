extern "C" {
#include "BarrelHolder.h"
}

void initBarrelHolder(std::unique_ptr<BarrelHolder>& barrelHolder) {
    barrelHolder->barrels = std::make_unique<MovableGameObject[]>(MAXIMUM_AMOUNT_OF_BARRELS);
    barrelHolder->numberOfElements = 0;
    barrelHolder->sizeOfArray = MAXIMUM_AMOUNT_OF_BARRELS;
}

void addBarrel(std::unique_ptr<BarrelHolder>& barrelHolder, std::unique_ptr<MovableGameObject>& barrel) {
    if (barrelHolder->numberOfElements == barrelHolder->sizeOfArray) {
        auto temp = std::make_unique<MovableGameObject[]>(barrelHolder->sizeOfArray * 2);

        for (int i = 0; i < barrelHolder->numberOfElements; i++) {
            temp[i] = std::move(barrelHolder->barrels[i]);
        }

        barrelHolder->barrels = std::move(temp);
        barrelHolder->sizeOfArray *= 2;
    }
    barrelHolder->barrels[barrelHolder->numberOfElements] = std::move(*barrel);
    barrelHolder->numberOfElements++;
}

void emptyBarrelHolder(std::unique_ptr<BarrelHolder>& barrelHolder) {
    // No need to explicitly delete, unique_ptr will handle it
    barrelHolder->barrels.reset();
    barrelHolder->numberOfElements = 0;
    barrelHolder->sizeOfArray = 0;
}

void updateBarrels(std::unique_ptr<BarrelHolder>& barrelHolder, float deltaTime) {
    for (int i = 0; i < barrelHolder->numberOfElements; i++) {
        barrelHolder->barrels[i].update(deltaTime);
    }
}