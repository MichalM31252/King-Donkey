#include "KeyActionHandler.h"

KeyActionHandler::KeyActionHandler(std::set<SDL_Keycode>* pressedKeys, std::set<SDL_Keycode>* releasedKeys, GameTime* gameTime, GameObjectContainer* gameObjectContainer, Menu* pauseMenu, Menu* gameOverMenu, Menu* startingScreenMenu, GameState* gameState)
	: pressedKeys(pressedKeys)
	, releasedKeys(releasedKeys)
	, gameTime(gameTime)
	, gameObjectContainer(gameObjectContainer)
	, pauseMenu(pauseMenu)
	, gameOverMenu(gameOverMenu)
	, startingScreenMenu(startingScreenMenu)
	, gameState(gameState)
{
}

void KeyActionHandler::handleInput() {
	handlePressedKeys();
	handleReleasedKeys();
}

// so the funny thing is that 
// in a set the first element that gets counted is the element with the smallest value
// esc key has value 27 
// everything else has a value around 10000
// so escape gets executed first always
// so I decided to iterate from the last element to the first one 

void KeyActionHandler::handlePressedKeys() {
	// Create copies of the key sets to safely iterate over
	std::set<SDL_Keycode> currentPressedKeys = *pressedKeys;
	for (auto it = currentPressedKeys.rbegin(); it != currentPressedKeys.rend(); ++it) {
		SDL_Keycode key = *it;

		// Skip if this key has already been handled
		if (handledKeys.find(key) != handledKeys.end()) {
			continue;
		}

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
			case SDLK_RETURN:
				onKeyPressEnter();
				break;
			case SDLK_ESCAPE:
				onKeyPressEsc();
				break;
			default:
				// Remove from handled keys if we don't actually handle it
				handledKeys.erase(key);
				break;
		}

		// Mark the key as handled
		handledKeys.insert(key);
	}
}

void KeyActionHandler::handleReleasedKeys() {
	std::set<SDL_Keycode> currentReleasedKeys = *releasedKeys;
	for (auto it = currentReleasedKeys.rbegin(); it != currentReleasedKeys.rend(); ++it) {
		SDL_Keycode key = *it;

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

		deleteHandledKey(key);
		deleteReleasedKey(key);
	}
}

Menu* KeyActionHandler::getCurrentActiveMenu() {
	switch (*gameState) {
		case GameState::PAUSE:
			return pauseMenu;
		case GameState::GAME_OVER:
			return gameOverMenu;
		case GameState::START:
			return startingScreenMenu;
		default:
			return nullptr;
	}
}

void KeyActionHandler::onKeyPressArrowUp() {
	if (*gameState == GameState::RUNNING) {
		auto player = gameObjectContainer->player;
		if (CollisionDetector::isGameObjectInsideAnyLadder(player, gameObjectContainer->ladderContainer)) {
			player->isClimbing = true;
			player->isFalling = false;
			player->isJumping = false;
			player->currentDirectionOfMovementY = DirectionY::UP;
			player->velocityY = DEFAULT_PLAYER_SPEED;
		}
	}
	else {
		Menu* currentMenu = getCurrentActiveMenu();
		currentMenu->selectPreviousOption();
	}
}

void KeyActionHandler::onKeyPressArrowDown() {
	if (*gameState == GameState::RUNNING) {
		auto player = gameObjectContainer->player;
		if (CollisionDetector::isGameObjectInsideAnyLadder(player, gameObjectContainer->ladderContainer)) {
			player->isClimbing = true;
			player->isFalling = false;
			player->isJumping = false;
			player->currentDirectionOfMovementY = DirectionY::DOWN;
			player->velocityY = DEFAULT_PLAYER_SPEED;
		}
	}
	else {
		Menu* currentMenu = getCurrentActiveMenu();
		currentMenu->selectNextOption();
	}
}

void KeyActionHandler::onKeyPressArrowRight() {
	if (*gameState == GameState::RUNNING) {
		auto player = gameObjectContainer->player;
		if (!player->isClimbing) {
			player->currentDirectionOfMovementX = DirectionX::RIGHT;
			player->velocityX = DEFAULT_PLAYER_SPEED;
		}
	}
}

void KeyActionHandler::onKeyPressArrowLeft() {
	if (*gameState == GameState::RUNNING) {
		auto player = gameObjectContainer->player;
		if (!player->isClimbing) {
			player->currentDirectionOfMovementX = DirectionX::LEFT;
			player->velocityX = DEFAULT_PLAYER_SPEED;
		}
	}
}

void KeyActionHandler::onKeyPressSpace() {
	if (*gameState == GameState::RUNNING) {
		gameObjectContainer->player->initJump();
	}
}

void KeyActionHandler::onKeyPressEnter() {
	if (*gameState == GameState::PAUSE) {
		handlePauseMenuSelection();
	}
	else if (*gameState == GameState::GAME_OVER) {
		handleGameOverMenuSelection();
	}
	else if (*gameState == GameState::START) {
		handleStartingScreenMenuSelection();
	}
}

void KeyActionHandler::onKeyPressEsc() {
	if (*gameState == GameState::RUNNING) {
		*gameState = GameState::PAUSE;
	}
	else if (*gameState == GameState::PAUSE) {
		*gameState = GameState::RUNNING;
	}
}

// "Resume", "Leaderboard", "Quit"
void KeyActionHandler::handlePauseMenuSelection() {
	switch (pauseMenu->selectedOptionIndex) {
		case 0: // Resume
			*gameState = GameState::RUNNING;
			break;
		case 1: // Leaderboard
			break;
		case 2: // Quit
			*gameState = GameState::QUIT;
			break;
	}
}

// "Retry", "Quit"
void KeyActionHandler::handleGameOverMenuSelection() {
	switch (gameOverMenu->selectedOptionIndex) {
		case 0: // Restart
			*gameState = GameState::RESTART;
			break;
		case 1: // Quit
			*gameState = GameState::QUIT;
			break;
	}
}

// "New Game", "Load Game", "Leaderboard", "Options", "Quit"
void KeyActionHandler::handleStartingScreenMenuSelection() {
	switch (startingScreenMenu->selectedOptionIndex) {
		case 0: // Start
			*gameState = GameState::RUNNING;
			break;
		case 1: // Load Game
			break;
		case 2: // Leaderboard
			break;
		case 3: // Options
			break;
		case 4: // Quit
			*gameState = GameState::QUIT;
			break;
	}
}

void KeyActionHandler::deleteHandledKey(SDL_Keycode key) {
	handledKeys.erase(key);
}
 
void KeyActionHandler::deleteReleasedKey(SDL_Keycode key) {
	releasedKeys->erase(key);
}

void KeyActionHandler::deletePressedKey(SDL_Keycode key) {
	pressedKeys->erase(key);
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

void KeyActionHandler::moveAllPressedKeysToReleasedKeys() {
	for (const auto& key : *pressedKeys) {
		if (releasedKeys->find(key) == releasedKeys->end()) {
			releasedKeys->insert(key);
		}
	}
	pressedKeys->clear();
}

void KeyActionHandler::moveAllHandledKeysToReleasedKeys() {
	for (const auto& key : handledKeys) {
		if (releasedKeys->find(key) == releasedKeys->end()) {
			releasedKeys->insert(key);
		}
	}
}