#define _USE_MATH_DEFINES

#include "KeyboardInputManager.h"
#include "ScreenManager.h" // temporary fix

KeyboardInputManager::KeyboardInputManager(std::shared_ptr<GameObjectContainer> gameObjectContainer, GameTime* gameTime)
    : event()
	, gameObjectContainer(gameObjectContainer)
    , gameTime(gameTime)
{
}

void KeyboardInputManager::handleEvents(bool& quit) { // rename this to handleInput and Keyboard manager to KeyboardController or something
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

void KeyboardInputManager::onKeyPressed(bool& quit){
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
		case SDLK_p:
            onKeyPressP();
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

void KeyboardInputManager::onKeyReleased() {
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

void KeyboardInputManager::onKeyReleasedArrowUp() {
	gameObjectContainer->player->accumulatedMoveUp = 0;
	if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::UP) {
		gameObjectContainer->player->velocityY = 0;
	}
}

void KeyboardInputManager::onKeyReleasedArrowLeft() {
    gameObjectContainer->player->accumulatedMoveLeft = 0;
	if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::LEFT) {
		gameObjectContainer->player->velocityX = 0;
	}
}

void KeyboardInputManager::onKeyReleasedArrowRight() {
    gameObjectContainer->player->accumulatedMoveRight = 0;
	if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::RIGHT) {
		gameObjectContainer->player->velocityX = 0;
	}
}

void KeyboardInputManager::onKeyReleasedArrowDown() {
    gameObjectContainer->player->accumulatedMoveDown = 0;
	if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::DOWN) {
		gameObjectContainer->player->velocityY = 0;
	}
}

void KeyboardInputManager::initializeQuit(bool& quit) {
	quit = true;
}

void KeyboardInputManager::onKeyPressArrowUp() {
	auto player = gameObjectContainer->player;
    if (CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
        player->isClimbing = true;
        player->isFalling = false;
        player->isJumping = false;
        player->currentDirectionOfMovementY = DirectionY::UP;
        player->velocityY = DEFAULT_PLAYER_SPEED;
	}
    else {
        player->isClimbing = false;
        player->currentDirectionOfMovementY = DirectionY::NONE;
        player->velocityY = 0;
    }
}

void KeyboardInputManager::onKeyPressArrowDown() {
    auto player = gameObjectContainer->player;
    if (CollisionDetector::isGameObjectInsideAnyLadder(player, gameObjectContainer->ladderContainer)) {
        player->isClimbing = true;
        player->isFalling = false;
        player->isJumping = false;
		player->currentDirectionOfMovementY = DirectionY::DOWN;
        player->velocityY = DEFAULT_PLAYER_SPEED;
    }
    else {
        player->isClimbing = false;
        player->currentDirectionOfMovementY = DirectionY::NONE;
        player->velocityY = 0;
    }
}

void KeyboardInputManager::onKeyPressArrowLeft() {
	auto player = gameObjectContainer->player;
	if (!player->isClimbing) {
		player->currentDirectionOfMovementX = DirectionX::LEFT;
        player->velocityX = DEFAULT_PLAYER_SPEED;
	}
}

void KeyboardInputManager::onKeyPressArrowRight() {
    auto player = gameObjectContainer->player;
	if (!player->isClimbing) {
		player->currentDirectionOfMovementX = DirectionX::RIGHT;
		player->velocityX = DEFAULT_PLAYER_SPEED;
	}
}

void KeyboardInputManager::onKeyPressSpace() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->initJump();
    }
}

void KeyboardInputManager::onKeyPressP() {
    if (gameTime->isPaused) {
        gameTime->resume();
    }
    else {
        gameTime->pause();
    }
}

void KeyboardInputManager::onKeyPressN(bool& quit) {
	onKeyPress1(quit);
}

void KeyboardInputManager::onKeyPress1(bool& quit) {
	quit = true;
}

void KeyboardInputManager::onKeyPress2(bool& quit) {
    onKeyPress1(quit);
}

void KeyboardInputManager::onKeyPress3(bool& quit) {
    onKeyPress1(quit);
}