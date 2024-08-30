#define _USE_MATH_DEFINES

#include "KeyboardManager.h"
#include "ScreenManager.h" // temporary fix

KeyboardManager::KeyboardManager() = default;

KeyboardManager::KeyboardManager(GameObjectContainer* gameObjectContainer) {
	this->gameObjectContainer = gameObjectContainer;
}

void KeyboardManager::handleEvents(bool& quit, double deltaTime, Player* player, int& startAnotherRound) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                onKeyPressed(quit, deltaTime, player, startAnotherRound);
                break;
            case SDL_KEYUP:
                onKeyReleased(player);
                break;
            case SDL_QUIT:
                initializeQuit(quit, startAnotherRound);
                break;
        }
    }
}

void KeyboardManager::onKeyPressed(bool& quit, double deltaTime, Player* player, int& startAnotherRound) const {
    player->startMovingAtSpeed(DEFAULT_PLAYER_SPEED);
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            initializeQuit(quit, startAnotherRound);
            break;
        case SDLK_UP:
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
        case SDLK_1:
            onKeyPress1(quit, startAnotherRound);
            break;
        case SDLK_2:
            onKeyPress2(quit, startAnotherRound);
            break;
        case SDLK_3:
            onKeyPress3(quit, startAnotherRound);
            break;
    }
}

void KeyboardManager::onKeyReleased(Player* player) const {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            onKeyReleasedArrowUp(player);
            break;
        case SDLK_LEFT:
            onKeyReleasedArrowLeft(player);
            break;
        case SDLK_RIGHT:
            onKeyReleasedArrowRight(player);
            break;
        case SDLK_DOWN:
            onKeyReleasedArrowDown(player);
            break;
    }
}

void KeyboardManager::onKeyReleasedArrowUp(Player* player) {
	player->accumulatedMoveUp = 0;
	if (player->currentDirectionOfMovement == 0) {
		player->currentDirectionOfMovement = -1;
	}
}

void KeyboardManager::onKeyReleasedArrowLeft(Player* player) {
	player->accumulatedMoveLeft = 0;
	if (player->currentDirectionOfMovement == 3) {
		player->currentDirectionOfMovement = -1;
	}
}

void KeyboardManager::onKeyReleasedArrowRight(Player* player) {
	player->accumulatedMoveRight = 0;
	if (player->currentDirectionOfMovement == 1) {
		player->currentDirectionOfMovement = -1;
	}
}

void KeyboardManager::onKeyReleasedArrowDown(Player* player) {
	player->accumulatedMoveDown = 0;
	if (player->currentDirectionOfMovement == 2) {
		player->currentDirectionOfMovement = -1;
	}
}

void KeyboardManager::initializeQuit(bool& quit, int& startAnotherRound) {
	quit = true;
	startAnotherRound = 0;
}

void KeyboardManager::onKeyPressArrowUp(double deltaTime, Player* player) {
	if (player->isInsideLadder) {
		player->isClimbing = true;

		ScreenManager::loadTexture(player, PLAYER_CLIMB_1);

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
		ScreenManager::loadTexture(player, PLAYER_CLIMB_1);
		player->startMovingDown(deltaTime);
	}
}

void KeyboardManager::onKeyPressSpace(Player* player) {
	player->initJump();
}

void KeyboardManager::onKeyPressN(bool& quit, int& startAnotherRound) {
	startAnotherRound = 1;
	quit = true;
}

void KeyboardManager::onKeyPress1(bool& quit, int& startAnotherRound) {
	startAnotherRound = 1;
	quit = true;
}

void KeyboardManager::onKeyPress2(bool& quit, int& startAnotherRound) {
	startAnotherRound = 2;
	quit = true;
}

void KeyboardManager::onKeyPress3(bool& quit, int& startAnotherRound) {
	startAnotherRound = 3;
	quit = true;
}

