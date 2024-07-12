extern "C" {
#include "Player.h"
#include "ScreenManager.h" // temporary solution
}

Player::Player() {
	*tag = "Player";
	isClimbing = false; // player
	isJumping = false; // player
	isInsideLadder = false; // player
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

void Player::startJumping() {
	isJumping = true;
	jumpHeightStop = ypos - DEFAULT_JUMP_HEIGHT;
}

void Player::stopJumping() {
	isJumping = false;
	jumpHeightStop = SCREEN_HEIGHT;
	accumulatedYMove = 0;
}

void Player::initJump() {
	checkIfJumpPossible = true;
	accumulatedYMove = 0;
}