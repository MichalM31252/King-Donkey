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
}

class Game {
	public:
		GameObjectFactory* gameObjectFactory;
		ScreenManager* screenManager;

		Game();

		void initGame();

		// Round manager
		/////////////////////////////////////////////////////////////////////////////////////
		
		void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);
		void handleRound(int startAnotherRound);

		/////////////////////////////////////////////////////////////////////////////////////

		// game object manager
		/////////////////////////////////////////////////////////////////////////////////////

		void handlePlayer();
		void handleBarrels(bool* quit, int* startAnotherRound);

		// Screen manager or texture manager
		/////////////////////////////////////////////////////////////////////////////////////

		void drawElements();
		void drawPlatforms();
		void drawLadders();
		void drawBarrels();

		// Game object manager or collision manager?
		/////////////////////////////////////////////////////////////////////////////////////

		void handleCollisionWithKong();
		void handleCollisionWithPrincess();
		void handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
		void handleCollisionWithLadder(int* flagLadder);
		void handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform);
		void handleCollisionWithJumping();

		/////////////////////////////////////////////////////////////////////////////////////

		void closeGame();
};