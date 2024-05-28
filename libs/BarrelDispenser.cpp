extern "C" {
#include "BarrelDispenser.h"
#include "ScreenManager.h" // temporary fix
}

void BarrelDispenser::initBarrelDispenser(BarrelDispenser* barrelDispenser) {
	barrelDispenser->barrelHolder = new BarrelHolder;
	initBarrelHolder(barrelDispenser->barrelHolder);
}

void BarrelDispenser::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void BarrelDispenser::updateBarrelDispenser(double deltaTime) {
	accumulatedTime += deltaTime;
	if (accumulatedTime >= DEFAULT_BARREL_SPAWN_RATE) {
		throwBarrel();
		accumulatedTime = 0.00;
	}
}

void BarrelDispenser::throwBarrel() {
	DynamicGameObject* barrel = new DynamicGameObject();
	ScreenManager::initGameObject(barrel, BARREL_1_FILENAME);
	barrel->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel->createSrcRect();
	barrel->createDestRect();
	barrel->objectSpeed = DEFAULT_BARREL_SPEED;

	addBarrel(barrelHolder, barrel);
}