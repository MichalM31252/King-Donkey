#define _USE_MATH_DEFINES

#include "KeyboardManager.h"
#include "ScreenManager.h" // temporary fix

KeyboardManager::KeyboardManager(GameObjectContainer* gameObjectContainer)
    : event()
	, gameObjectContainer(gameObjectContainer)
{
}

void KeyboardManager::handleEvents(bool& quit) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                onKeyPressed(quit);
                break;
            case SDL_KEYUP:
                onKeyReleased();
                break;
            case SDL_QUIT:
                initializeQuit(quit);
                break;
			default:
				break;
        }
    }
}

void KeyboardManager::onKeyPressed(bool& quit){
    gameObjectContainer->player->startMovingAtSpeed(DEFAULT_PLAYER_SPEED);
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            // close the game static method
            initializeQuit(quit);
            break;
        case SDLK_UP:
            onKeyPressArrowUp();
            break;
        case SDLK_LEFT:
            onKeyPressArrowLeft();
            break;
        case SDLK_RIGHT:
            onKeyPressArrowRight();
            break;
        case SDLK_DOWN:
            onKeyPressArrowDown();
            break;
        case SDLK_SPACE:
            onKeyPressSpace();
            break;
        case SDLK_n:
            onKeyPressN(quit);
            break;
        case SDLK_1:
            onKeyPress1(quit);
            break;
        case SDLK_2:
            onKeyPress2(quit);
            break;
        case SDLK_3:
            onKeyPress3(quit);
            break;
        default:
            break;
    }
}

void KeyboardManager::onKeyReleased() {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            onKeyReleasedArrowUp();
            break;
        case SDLK_LEFT:
            onKeyReleasedArrowLeft();
            break;
        case SDLK_RIGHT:
            onKeyReleasedArrowRight();
            break;
        case SDLK_DOWN:
            onKeyReleasedArrowDown();
            break;
        default:
            break;
    }
}

void KeyboardManager::onKeyReleasedArrowUp() {
	gameObjectContainer->player->accumulatedMoveUp = 0;
	if (gameObjectContainer->player->currentDirectionOfMovement == 0) {
        gameObjectContainer->player->objectSpeed = 0;
	}
}

void KeyboardManager::onKeyReleasedArrowLeft() {
    gameObjectContainer->player->accumulatedMoveLeft = 0;
	if (gameObjectContainer->player->currentDirectionOfMovement == 3) {
        gameObjectContainer->player->objectSpeed = 0;
		// gameObjectContainer->player->currentDirectionOfMovement = 0; // z tym animacja idle nie dziala
	}
}

void KeyboardManager::onKeyReleasedArrowRight() {
    gameObjectContainer->player->accumulatedMoveRight = 0;
	if (gameObjectContainer->player->currentDirectionOfMovement == 1) {
        gameObjectContainer->player->objectSpeed = 0;
        // gameObjectContainer->player->currentDirectionOfMovement = 0; // z tym animacja idle nie dziala
	}
}

void KeyboardManager::onKeyReleasedArrowDown() {
    gameObjectContainer->player->accumulatedMoveDown = 0;
	if (gameObjectContainer->player->currentDirectionOfMovement == 2) {
        gameObjectContainer->player->objectSpeed = 0;
	}
}

void KeyboardManager::initializeQuit(bool& quit) {
	quit = true;
}

void KeyboardManager::onKeyPressArrowUp() {
    if (CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
        gameObjectContainer->player->isClimbing = true;

		ScreenManager::loadTexture(gameObjectContainer->player, PLAYER_CLIMB_1); // THIS SHOOUDNT BE HERE

        gameObjectContainer->player->startMovingUp();
	}
    else {
        gameObjectContainer->player->isClimbing = false;
    }
}

void KeyboardManager::onKeyPressArrowLeft() {
	if (!gameObjectContainer->player->isClimbing) {
        gameObjectContainer->player->startMovingLeft();
	}
}

void KeyboardManager::onKeyPressArrowRight() {
	if (!gameObjectContainer->player->isClimbing) {
        gameObjectContainer->player->startMovingRight();
	}
}

void KeyboardManager::onKeyPressArrowDown() {
	if (CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
        gameObjectContainer->player->isClimbing = true;

		ScreenManager::loadTexture(gameObjectContainer->player, PLAYER_CLIMB_1); // THIS SHOOUDNT BE HERE

        gameObjectContainer->player->startMovingDown();
	}
    else {
        gameObjectContainer->player->isClimbing = false;
    }
}

void KeyboardManager::onKeyPressSpace() {
    gameObjectContainer->player->initJump();
}

void KeyboardManager::onKeyPressN(bool& quit) {
	onKeyPress1(quit);
}

void KeyboardManager::onKeyPress1(bool& quit) {
	quit = true;
}

void KeyboardManager::onKeyPress2(bool& quit) {
    onKeyPress1(quit);
}

void KeyboardManager::onKeyPress3(bool& quit) {
    onKeyPress1(quit);
}