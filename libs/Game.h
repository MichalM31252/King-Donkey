#pragma once

extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "ScreenManager.h"
#include "KeyboardManager.h"
#include "Constants.h"
#include "Player.h"
#include "Platform.h"
#include "BarrelHolder.h"
#include "GameObjectFactory.h"
#include "RoundManager.h"
}

extern "C++" {
#include <memory>
}

class Game {
public:
    std::unique_ptr<GameObjectContainer> gameObjectContainer;
    std::unique_ptr<GameObjectFactory> gameObjectFactory;
    std::unique_ptr<ScreenManager> screenManager;
    std::unique_ptr<CollisionResolver> collisionResolver;
    std::unique_ptr<RoundManager> roundManager;

	Game();

	void initGame();
	void closeGame();
};