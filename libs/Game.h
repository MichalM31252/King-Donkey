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

class Game {
public:
    GameObjectContainer* gameObjectContainer;
    GameObjectFactory* gameObjectFactory;
    ScreenManager* screenManager;
    CollisionResolver* collisionResolver;
    RoundManager* roundManager;

	Game();

	void initGame();
	void closeGame();
};