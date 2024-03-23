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
		
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;

		GameObjectManager* gameObjectManager;
		ScreenManager* screenManager;

		void initGame();

		void createFramerate();
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		

		void handleRound(int startAnotherRound);

		void createBoard(int boardId);

		void createPlayer();
		void createDonkeyKong();
		void createPrincess();

		void createPlatforms1();
		void createLadders1();

		void createPlatforms2();
		void createLadders2();

		void createPlatforms3();
		void createLadders3();

		void createBarrels();

		// REMOVE SCREEN MANAGER WHERE ITS NOT NEEDED

		void handlePlayer();
		void handleBarrels(bool* quit, int* startAnotherRound);

		void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);

		void handleCollisionWithKong();
		void handleCollisionWithPrincess();
		void handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
		void handleCollisionWithLadder(int* flagLadder);

		void handleCollisionWithPlatform(DynamicGameObject *gameObject, int* flagPlatform);
		void handleCollisionWithJumping();

		

		void closeGame();
		// void closeGame(ScreenManager& screenManager);


		// move to GameObjectManager

		void drawElements();
		void drawPlatforms();
		void drawLadders();
		void drawBarrels();
};