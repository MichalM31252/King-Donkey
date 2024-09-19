#include "Player.h"
#include "ScreenManager.h" // temporary solution

Player::Player()
	: isInsideLadder(false)
	, isJumping(false)
	, isClimbing(false)
	, checkIfJumpPossible(false)
	, jumpHeightStop(SCREEN_HEIGHT)
{
}

void Player::startClimbing() {
	isClimbing = true;
}

void Player::stopClimbing() {
	isClimbing = false;
}

void Player::jump(double deltaTime) {
	accumulatedMoveUp -= deltaTime * gravity;
	int pixelsToMove = accumulatedMoveUp / 1;
	if (pixelsToMove <= -1) {
		ypos -= 1;
		accumulatedMoveUp += 1;
	}
}

void Player::startJumping() {
	isJumping = true;
	jumpHeightStop = ypos - DEFAULT_JUMP_HEIGHT;
}

void Player::stopJumping() {
	isJumping = false;
	jumpHeightStop = SCREEN_HEIGHT;
	accumulatedMoveDown = 0;
	accumulatedMoveUp = 0;
}

void Player::initJump() {
	checkIfJumpPossible = true;
	accumulatedMoveDown = 0;
	accumulatedMoveUp = 0;
}

void Player::loadNextRunningSprite() {
	if (this->currentSpriteId == 1) {
		// ScreenManager::loadTexture(this, PLAYER_1_FILENAME);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 2) {
		// ScreenManager::loadTexture(this, PLAYER_2_FILENAME);
		this->currentSpriteId++;
	}
	else {
		// ScreenManager::loadTexture(this, PLAYER_3_FILENAME);
		this->currentSpriteId = 1;
	}
}

void Player::loadJumpingSprite() const {
	// ScreenManager::loadTexture(this, PLAYER_3_FILENAME);
}

void Player::loadClimbingSprite() const {
	// ScreenManager::loadTexture(this, PLAYER_CLIMB_1);
}

void Player::loadNextClimbingSprite() const {

}

bool Player::isPlayerJumping() const {
	return this->isJumping;
}

bool Player::isPlayerMovingVertically() const {
	if (currentDirectionOfMovement == 0 || currentDirectionOfMovement == 2) {
		return true;
	}
	return false;
}

void Player::startAccumulatingDistance(double deltaTime) {
	if (isPlayerMovingVertically()) { // up or down
		if (isClimbing) {
			if (currentDirectionOfMovement == 0) {
				accumulatedMoveUp += deltaTime * objectSpeed;
			}
			else {
				accumulatedMoveDown += deltaTime * objectSpeed;
			}
		}
	}
	else {
		MovableGameObject::startAccumulatingDistance(deltaTime);
	}
}

