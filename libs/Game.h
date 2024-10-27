#pragma once

#include <memory>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ScreenManager.h"
#include "KeyboardInputManager.h"
#include "Constants.h"
#include "Player.h"
#include "Platform.h"
#include "BarrelContainer.h"
#include "LevelLoader.h"
#include "GameObjectManager.h"
#include "GameTime.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

// EVERY SHARED POINTER SHOULD BE PASSED BY CONST REFERENCE FIX THIS IN THE FUTURE

class Game {
public:
	// GameTime gameTime;
	GameTime gameTime;
	std::shared_ptr<GameObjectContainer> gameObjectContainer;
	ScreenManager screenManager;
	LevelLoader levelLoader;
	KeyboardInputManager keyboardInputManager;
	GameObjectManager gameObjectManager;

	Game();

	[[noreturn]] void startGame();
	[[noreturn]] void runGame();
	[[noreturn]] void closeGame() const;
};