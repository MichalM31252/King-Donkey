extern "C" {
#include "BarrelFactory.h"
#include "ScreenManager.h" // temporary fix
}

void BarrelFactory::initBarrelFactory(BarrelFactory* barrelFactory) const{
	barrelFactory->barrelHolder = std::make_unique<BarrelHolder>();
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
	auto barrel = std::make_unique<MovableGameObject>();
	ScreenManager::initGameObject(barrel.get(), BARREL_1_FILENAME);

	barrel->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel->createSrcRect();
	barrel->createDestRect();
	barrel->objectSpeed = DEFAULT_BARREL_SPEED;

	addBarrel(barrelHolder, std::move(barrel));
}