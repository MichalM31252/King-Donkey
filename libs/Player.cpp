#include "Player.h"
#include "ScreenManager.h" // temporary solution

Player::Player()
	: isJumping(false)
	, distanceTravelledFromLastRunningSprite(20) // remove magic number
	, distanceTravelledFromLastClimbingSprite(20)
	, isClimbing(false)
	, checkIfJumpPossible(false)
	, jumpHeightStop(SCREEN_HEIGHT)
	, currentClimbingSpriteId(0)
	, currentRunningSpriteId(0)
{
}

void Player::update(double deltaTime) {
	this->updatePosition();
	startAccumulatingDistance(deltaTime);
	stayInBounds();
	updatePositionCoordinates();
}

void Player::updatePosition() {
	int pixelsToMove = 0;
	if (accumulatedMoveRight > 1.0f) {
		pixelsToMove = (int)accumulatedMoveRight;
		xpos += pixelsToMove;
		accumulatedMoveRight -= pixelsToMove;
	}
	if (accumulatedMoveDown > 1.0f) {
		pixelsToMove = (int)accumulatedMoveDown;
		ypos += pixelsToMove;
		accumulatedMoveDown -= pixelsToMove;
	}
	if (accumulatedMoveLeft > 1.0f) {
		pixelsToMove = (int)accumulatedMoveLeft;
		xpos -= pixelsToMove;
		accumulatedMoveLeft -= pixelsToMove;
	}
	if (accumulatedMoveUp > 1.0f) {
		pixelsToMove = (int)accumulatedMoveUp;
		ypos -= pixelsToMove;
		accumulatedMoveUp -= pixelsToMove;
	}

	if (!isJumping && !isFalling) {
		distanceTravelledFromLastRunningSprite += pixelsToMove; // move to movableGameObject or not idk
	}

	if (isClimbing) {
		distanceTravelledFromLastClimbingSprite += pixelsToMove;
	}
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
	distanceTravelledFromLastRunningSprite = 0; // move to movableGameObject or not idk
}

void Player::initJump() {
	checkIfJumpPossible = true;
	accumulatedMoveDown = 0;
	accumulatedMoveUp = 0;
}

void Player::loadNextRunningSprite() {
	bool shouldSpriteBeReversed;
	if (directionOfMovementX == RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}

	if (this->currentSpriteId == 1) {
		ScreenManager::loadTexture(this, PLAYER_1_FILENAME, shouldSpriteBeReversed);
		this->currentSpriteId++;
	}
	else if (this->currentSpriteId == 2) {
		ScreenManager::loadTexture(this, PLAYER_2_FILENAME, shouldSpriteBeReversed);
		this->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, PLAYER_3_FILENAME, shouldSpriteBeReversed);
		this->currentSpriteId = 1;
	}
}

void Player::loadJumpingSprite() {
	bool shouldSpriteBeReversed;
	if (directionOfMovementX == RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}

	ScreenManager::loadTexture(this, PLAYER_3_FILENAME, shouldSpriteBeReversed);
}

void Player::loadClimbingSprite() {
	ScreenManager::loadTexture(this, PLAYER_CLIMB_1, false);
	currentClimbingSpriteId = 1;
}

void Player::loadNextClimbingSprite(){
	if (currentClimbingSpriteId == 1) {
		ScreenManager::loadTexture(this, PLAYER_CLIMB_2, false);
		currentClimbingSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, PLAYER_CLIMB_1, false);
		currentClimbingSpriteId = 1;
	}
}

void Player::loadIdleSprite() {
	bool shouldSpriteBeReversed;
	if (directionOfMovementX == RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}
	
	ScreenManager::loadTexture(this, PLAYER_1_FILENAME, shouldSpriteBeReversed);
	currentRunningSpriteId = 1;
}

bool Player::isPlayerJumping() const {
	return this->isJumping;
}

bool Player::isPlayerMovingVertically() const {
	if ((directionOfMovementY == UP || directionOfMovementY == DOWN) && velocityY > 0) {
		return true;
	}
	return false;
}

void Player::startAccumulatingDistance(double deltaTime) {
	if (isPlayerMovingVertically()) { // up or down
		if (isClimbing) {
			if (directionOfMovementY == UP && velocityY > 0) {
				accumulatedMoveUp += deltaTime * velocityY;
			}
			if (directionOfMovementY == DOWN && velocityY > 0) {
				accumulatedMoveDown += deltaTime * velocityY;
			}
		}
	}
	else {
		MovableGameObject::startAccumulatingDistance(deltaTime);
	}
}

