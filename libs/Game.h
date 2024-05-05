#pragma once

extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "./game_screen/ScreenManager.h"
#include "./game_events/KeyboardManager.h"
#include "./Constants.h"
#include "./game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
#include "./Platform.h"
#include "./BarrelHolder.h"
#include "./GameObjectManager.h"
}

class Game {
	public:
		GameObjectManager* gameObjectManager;
		ScreenManager* screenManager;

		Game();

		void initGame();


		void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);
		void handleRound(int startAnotherRound);

		void handlePlayer();
		void handleBarrels(bool* quit, int* startAnotherRound);

		void drawElements();
		void drawPlatforms();
		void drawLadders();
		void drawBarrels();

		void handleCollisionWithKong();
		void handleCollisionWithPrincess();
		void handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
		void handleCollisionWithLadder(int* flagLadder);

		void handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform);
		void handleCollisionWithJumping();

		void closeGame();
		// void closeGame(ScreenManager& screenManager);
};