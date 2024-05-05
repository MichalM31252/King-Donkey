extern "C" {
#include "Player.h"
}

Player::Player() {
	*tag = "Player";
}

void Player::jump(double deltaTime) {
	ScreenManager::loadTexture(this, PLAYER_3_FILENAME);
	accumulatedYMove -= deltaTime * gravity;
	int pixelsToMove = accumulatedYMove / 1;
	if (pixelsToMove <= -1) {
		ypos -= 1;
		accumulatedYMove += 1;
	}
}