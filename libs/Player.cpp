#include "Player.h"
#include "ScreenManager.h" // temporary solution

Player::Player()
	: isJumping(false)
	, isClimbing(false) 
	, currentRunningSpriteId(0) 
	, currentClimbingSpriteId(0) 
	, distanceTravelledFromLastRunningSprite(20) // remove magic number 
	, distanceTravelledFromLastClimbingSprite(20) 
	, jumpHeightStop(SCREEN_HEIGHT) 
	, checkIfJumpPossible(false)
{
}

void Player::update(double deltaTime) {
	this->updatePosition();
	accumulateDistance(deltaTime);
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
	if (currentDirectionOfMovementX == DirectionX::RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}

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

	if (shouldSpriteBeReversed) {
		ScreenManager::flipTextureHorizontally(this->sprite);
	}
}

void Player::loadJumpingSprite() {
	bool shouldSpriteBeReversed;
	if (currentDirectionOfMovementX == DirectionX::RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}

	ScreenManager::loadTexture(this, PLAYER_3_FILENAME);

	if (shouldSpriteBeReversed) {
		ScreenManager::flipTextureHorizontally(this->sprite);
	}
}

void Player::loadClimbingSprite() {
	ScreenManager::loadTexture(this, PLAYER_CLIMB_1);
	currentClimbingSpriteId = 1;
}

void Player::loadNextClimbingSprite(){
	if (currentClimbingSpriteId == 1) {
		ScreenManager::loadTexture(this, PLAYER_CLIMB_1);
		currentClimbingSpriteId++;
	}
	else {
		ScreenManager::loadTexture(this, PLAYER_CLIMB_1);
		ScreenManager::flipTextureHorizontally(this->sprite);
		currentClimbingSpriteId = 1;
	}
}

void Player::loadIdleSprite() {
	bool shouldSpriteBeReversed;
	if (currentDirectionOfMovementX == DirectionX::RIGHT) {
		shouldSpriteBeReversed = false;
	}
	else {
		shouldSpriteBeReversed = true;
	}
	
	ScreenManager::loadTexture(this, PLAYER_1_FILENAME);
	if (shouldSpriteBeReversed) {
		ScreenManager::flipTextureHorizontally(this->sprite);
	}

	currentRunningSpriteId = 1;
}

bool Player::isMovingVertically() const {
	if ((currentDirectionOfMovementY == DirectionY::UP || currentDirectionOfMovementY == DirectionY::DOWN) && velocityY > 0) {
		return true;
	}
	return false;
}

void Player::accumulateDistance(double deltaTime) {
	if (currentDirectionOfMovementY == DirectionY::UP && velocityY > 0) {
		accumulatedMoveUp += deltaTime * velocityY;
	}
	else if (currentDirectionOfMovementY == DirectionY::DOWN && velocityY > 0) {
		accumulatedMoveDown += deltaTime * velocityY;
	}
	else {
		MovableGameObject::accumulateDistance(deltaTime);
	}
}

