#include "BarrelFactory.h"
#include "ScreenManager.h"


BarrelFactory::BarrelFactory(BarrelContainer* barrelHolder) {
	this->barrelHolder = barrelHolder;
	accumulatedTime = DEFAULT_BARREL_SPAWN_RATE;
}

void BarrelFactory::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void BarrelFactory::update(double deltaTime) {
	accumulatedTime += deltaTime;
	if (accumulatedTime >= DEFAULT_BARREL_SPAWN_RATE) {
		throwBarrel();
		accumulatedTime -= DEFAULT_BARREL_SPAWN_RATE;
	}
}

void BarrelFactory::throwBarrel() {
	auto* barrel = new MovableGameObject();
	ScreenManager::initGameObject(barrel, BARREL_1_FILENAME);

	barrel->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel->createSrcRect();
	barrel->createDestRect();
	barrel->objectSpeed = DEFAULT_BARREL_SPEED;

	barrelHolder->addBarrel(barrel);
}