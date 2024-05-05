#define _USE_MATH_DEFINES

extern "C" {
#include "KeyboardManager.h"
}

void KeyboardManager::handleEvents(bool* quit, double deltaTime, Player* player, int *startAnotherRound) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				onKeyDown(quit, deltaTime, player, startAnotherRound);
				break;
			case SDL_KEYUP:
				onKeyUp(player);
				break;
			case SDL_QUIT:
				initializeQuit(quit, startAnotherRound);
				break;
		}
	}
}

void KeyboardManager::onKeyDown(bool* quit, double deltaTime, Player* player, int* startAnotherRound) {
	player->moveStart(DEFAULT_PLAYER_SPEED);
	switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			initializeQuit(quit, startAnotherRound);
			break;
		case SDLK_UP: // why is he still in the ladder 
			onKeyPressArrowUp(deltaTime, player);
			break;
		case SDLK_LEFT:
			onKeyPressArrowLeft(deltaTime, player);
			break;
		case SDLK_RIGHT:
			onKeyPressArrowRight(deltaTime, player);
			break;
		case SDLK_DOWN:
			onKeyPressArrowDown(deltaTime, player);
			break;
		case SDLK_SPACE:
			onKeyPressSpace(player);
			break;
		case SDLK_n:
			onKeyPressN(quit, startAnotherRound);
			break;
		case SDLK_1: // load level 1
			onKeyPress1(quit, startAnotherRound);
			break;
		case SDLK_2: // load level 2
			onKeyPress2(quit, startAnotherRound);
			break;
		case SDLK_3: // load level 3
			onKeyPress3(quit, startAnotherRound);
			break;
	}
}

void KeyboardManager::onKeyUp(Player* player) { // yeah this needs to be fixed you need to check if space was let go or arrow was let go
	player->stopMove(); 
}

void KeyboardManager::initializeQuit(bool* quit, int* startAnotherRound) {
	*quit = true;
	*startAnotherRound = 0;
}

void KeyboardManager::onKeyPressArrowUp(double deltaTime, Player* player) {
	if (player->isInsideLadder) {
		player->isClimbing = true; // the problem is most likely with this 

		ScreenManager::loadTexture(player, PLAYER_CLIMB);

		player->startMovingUp(deltaTime);
	}
}

void KeyboardManager::onKeyPressArrowLeft(double deltaTime, Player* player) {
	if (!player->isClimbing) {
		player->startMovingLeft(deltaTime);
	}
}

void KeyboardManager::onKeyPressArrowRight(double deltaTime, Player* player) {
	if (!player->isClimbing) {
		player->startMovingRight(deltaTime);
	}
}

void KeyboardManager::onKeyPressArrowDown(double deltaTime, Player* player) {
	if (player->isInsideLadder) {
		player->isClimbing = true;

		ScreenManager::loadTexture(player, PLAYER_CLIMB);

		player->startMovingDown(deltaTime);
	}
}

void KeyboardManager::onKeyPressSpace(Player* player) {
	player->initJump();
}

void KeyboardManager::onKeyPressN(bool* quit, int *startAnotherRound) {
	*startAnotherRound = 1;
	*quit = true;
}

void KeyboardManager::onKeyPress1(bool* quit, int* startAnotherRound) {
	*startAnotherRound = 1;
	*quit = true;
}

void KeyboardManager::onKeyPress2(bool* quit, int* startAnotherRound) {
	*startAnotherRound = 2;
	*quit = true;
}

void KeyboardManager::onKeyPress3(bool* quit, int* startAnotherRound) {
	*startAnotherRound = 3;
	*quit = true;
}

