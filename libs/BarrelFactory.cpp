#include "BarrelFactory.h"
#include "ScreenManager.h"

BarrelFactory::BarrelFactory(std::shared_ptr<BarrelContainer> barrelContainer)
	: accumulatedTime(DEFAULT_BARREL_SPAWN_RATE)
	, barrelContainer(barrelContainer)
{
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
	auto barrel = std::make_shared<Barrel>();
	ScreenManager::loadTexture(barrel.get(), BARREL_1_FILENAME);

	barrel->setPosition(STARTING_X_DONKEY_KONG + DONKEY_KONG_WIDTH, STARTING_Y_DONKEY_KONG);
	barrel->createSrcRect();
	barrel->createDestRect();

	barrel->startMovingRight(); // rename this to setHorizontalDirection
	barrel->startMovingHorizontallyAtSpeed(DEFAULT_BARREL_SPEED); // rename this to setHorizontalSpeed

	barrelContainer->addBarrel(barrel);
}