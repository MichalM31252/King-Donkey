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

void Player::loadNextRunningSprite() {
	if (this->currentSpriteId == 1) {
		ScreenManager::loadTexture(this, PLAYER_1_FILENAME);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 2) {
		ScreenManager::loadTexture(this, PLAYER_2_FILENAME);
		this->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, PLAYER_3_FILENAME);
		this->currentSpriteId = 1;
	}
}

void Player::loadJumpingSprite(){
	ScreenManager::loadTexture(this, PLAYER_3_FILENAME);
}

void Player::loadClimbingSprite(){
	ScreenManager::loadTexture(this, PLAYER_CLIMB);
}