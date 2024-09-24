#pragma once

#include <memory>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ScreenManager.h"
#include "KeyboardManager.h"
#include "Constants.h"
#include "Player.h"
#include "Platform.h"
#include "BarrelHolder.h"
#include "LevelLoader.h"
#include "GameObjectManager.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class Game {
public:
	std::unique_ptr<GameObjectContainer> gameObjectContainer;
	std::unique_ptr<ScreenManager> screenManager;
	std::unique_ptr<LevelLoader> levelLoader;
	std::unique_ptr<KeyboardManager> keyboardManager;
	std::unique_ptr<GameObjectManager> gameObjectManager;

	Game();

	void initGame() const;
	void closeGame() const;
};