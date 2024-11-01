#include "KeyActionHandler.h"

KeyActionHandler::KeyActionHandler(std::set<SDL_Keycode>* pressedKeys, std::set<SDL_Keycode>* releasedKeys, GameTime* gameTime, GameObjectContainer* gameObjectContainer)
	: pressedKeys(pressedKeys)
	, releasedKeys(releasedKeys)
	, gameTime(gameTime)
	, gameObjectContainer(gameObjectContainer)
{
}

void KeyActionHandler::handleInput() {
	for (auto key : *pressedKeys) {
		printf("Key pressed: %d\n", key);

		// Skip if this key has already been handled
		if (handledKeys.find(key) != handledKeys.end()) {
			continue;
		}

		// Mark the key as handled before processing
		handledKeys.insert(key);

		switch (key) {
			case SDLK_UP:
				onKeyPressArrowUp();
				break;
			case SDLK_DOWN:
				onKeyPressArrowDown();
				break;
			case SDLK_LEFT:
				onKeyPressArrowLeft();
				break;
			case SDLK_RIGHT:
				onKeyPressArrowRight();
				break;
			case SDLK_SPACE:
				onKeyPressSpace();
				break;
			case SDLK_ESCAPE:
				onKeyPressEsc();
				break;
			default:
				// Remove from handled keys if we don't actually handle it
				handledKeys.erase(key);
				break;
		}
	}

	for (auto key : *releasedKeys) {
		printf("Key released: %d\n", key);

		// Clear the handled status for this key
		clearHandledKey(key);

		switch (key) {
			case SDLK_UP:
				onKeyReleasedArrowUp();
				break;
			case SDLK_DOWN:
				onKeyReleasedArrowDown();
				break;
			case SDLK_LEFT:
				onKeyReleasedArrowLeft();
				break;
			case SDLK_RIGHT:
				onKeyReleasedArrowRight();
				break;
			default:
				break;
		}
	}
}

// PROBLEMEM JEST TO ŻE KAŻDA Z TYCH FUNCKJI JEST WYKONYWANA RAZ TYLKO JAK WCISNIESZ I PRZERYWANA JAK PUSCICSZ
// CZYLI TYLKO RAZ NA POCZATKU SPRZAWDZI CZY JEST WEWNATRZ DRABINY
void KeyActionHandler::onKeyPressArrowUp() {
	if (!gameTime->isPaused) {
		auto player = gameObjectContainer->player;
		if (CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
			player->isClimbing = true;
			player->isFalling = false;
			player->isJumping = false;
			player->currentDirectionOfMovementY = DirectionY::UP;
			player->velocityY = DEFAULT_PLAYER_SPEED;
		}
	}
}

void KeyActionHandler::onKeyPressArrowDown() {
	if (!gameTime->isPaused) {
		auto player = gameObjectContainer->player;
		if (CollisionDetector::isGameObjectInsideAnyLadder(player, gameObjectContainer->ladderContainer)) {
			player->isClimbing = true;
			player->isFalling = false;
			player->isJumping = false;
			player->currentDirectionOfMovementY = DirectionY::DOWN;
			player->velocityY = DEFAULT_PLAYER_SPEED;
		}
	}
}

void KeyActionHandler::onKeyPressArrowRight() {
    if (!gameTime->isPaused) {
        auto player = gameObjectContainer->player;
        if (!player->isClimbing) {
            player->currentDirectionOfMovementX = DirectionX::RIGHT;
            player->velocityX = DEFAULT_PLAYER_SPEED;
        }
    }
}

void KeyActionHandler::onKeyPressArrowLeft() {
    if (!gameTime->isPaused) {
        auto player = gameObjectContainer->player;
        if (!player->isClimbing) {
            player->currentDirectionOfMovementX = DirectionX::LEFT;
            player->velocityX = DEFAULT_PLAYER_SPEED;
        }
    }
}

void KeyActionHandler::onKeyPressSpace() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->initJump();
    }
}

void KeyActionHandler::clearHandledKey(SDL_Keycode key) {
	handledKeys.erase(key);
}

void KeyActionHandler::onKeyPressEsc() {
    if (!gameTime->isPaused) {
        gameTime->pause();
        // show menu

    }
    else {
        gameTime->resume();
		// hide menu
    }
}


void KeyActionHandler::onKeyReleasedArrowUp() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->accumulatedMoveUp = 0;
        if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::UP) {
			gameObjectContainer->player->velocityY= 0;
        }
    }
}

void KeyActionHandler::onKeyReleasedArrowLeft() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->accumulatedMoveLeft = 0;
        if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::LEFT) {
            gameObjectContainer->player->velocityX = 0;
        }
    }
}

void KeyActionHandler::onKeyReleasedArrowRight() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->accumulatedMoveRight = 0;
        if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::RIGHT) {
            gameObjectContainer->player->velocityX = 0;
        }
    }
}

void KeyActionHandler::onKeyReleasedArrowDown() {
    if (!gameTime->isPaused) {
        gameObjectContainer->player->accumulatedMoveDown = 0;
	    if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::DOWN) {
		    gameObjectContainer->player->velocityY = 0;
	    }
    }
}