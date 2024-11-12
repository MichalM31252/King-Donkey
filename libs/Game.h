#pragma once

#include <memory>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ScreenManager.h"
#include "KeyCollector.h"
#include "KeyActionHandler.h"
#include "Constants.h"
#include "Player.h"
#include "Platform.h"
#include "BarrelContainer.h"
#include "LevelLoader.h"
#include "GameObjectManager.h"
#include "GameTime.h"
#include "Menu.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

// EVERY SHARED POINTER SHOULD BE PASSED BY CONST REFERENCE FIX THIS IN THE FUTURE

class Game {
public:
	GameTime gameTime;
	std::shared_ptr<GameObjectContainer> gameObjectContainer;
	ScreenManager screenManager;
	LevelLoader levelLoader;
	KeyCollector keyCollector;
	Menu pauseMenu; // will probably add startingScreenMenu and gameOverMenu
	KeyActionHandler keyActionHandler;
	GameObjectManager gameObjectManager;

	Game();

	[[noreturn]] void startGame();
	[[noreturn]] void runGame();
	[[noreturn]] void closeGame() const;
};