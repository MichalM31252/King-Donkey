#include "Barrel.h"

void Barrel::loadNextSprite() {
	if (this->currentSpriteId == 1) {
		ScreenManager::loadTexture(this, BARREL_1_FILENAME, false);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 2) {
		ScreenManager::loadTexture(this, BARREL_2_FILENAME, false);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 3) {
		ScreenManager::loadTexture(this, BARREL_3_FILENAME, false);
		this->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, BARREL_4_FILENAME, false);
		this->currentSpriteId = 1;
	}
}
