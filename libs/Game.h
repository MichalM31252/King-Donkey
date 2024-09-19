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
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class Game {
public:
	std::unique_ptr<GameObjectContainer> gameObjectContainer;
	std::unique_ptr<ScreenManager> screenManager;
	std::unique_ptr<LevelLoader> levelLoader;
	std::unique_ptr<KeyboardManager> keyboardManager;

	// GameObjectManager
	std::unique_ptr<CollisionResolver> collisionResolver;
	std::unique_ptr<CollisionDetector> collisionDetector;
	std::unique_ptr<PhysicsManager> physicsManager;
	//

	Game();

	void initGame() const;
	void closeGame() const;
};