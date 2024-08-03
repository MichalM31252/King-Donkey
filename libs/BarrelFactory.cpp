extern "C" {
#include "BarrelFactory.h"
#include "ScreenManager.h" // temporary fix
}

void BarrelFactory::initBarrelFactory(BarrelFactory* barrelFactory) {
	barrelFactory->barrelHolder = new BarrelHolder;
	initBarrelHolder(barrelFactory->barrelHolder);
}

void BarrelFactory::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void BarrelFactory::update(double deltaTime) {
	accumulatedTime += deltaTime;
	if (accumulatedTime >= DEFAULT_BARREL_SPAWN_RATE) {
		throwBarrel();
		accumulatedTime = 0.00;
	}
}

void BarrelFactory::throwBarrel() {
	MovableGameObject* barrel = new MovableGameObject();
	ScreenManager::initGameObject(barrel, BARREL_1_FILENAME); // this needs refactoring 

	barrel->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel->createSrcRect();
	barrel->createDestRect();
	barrel->objectSpeed = DEFAULT_BARREL_SPEED;

	addBarrel(barrelHolder, barrel);
}