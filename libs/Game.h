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
#include "./game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h" // // // // // //
#include "./Platform.h" // // // //
#include "./BarrelHolder.h" // // // 
#include "./GameObjectManager.h"
}

class Game {
	public:
		
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		
		// Place in GameObjectContainer 
		PlatformHolder* platformHolder; 
		LadderHolder* ladderHolder;
		BarrelDispenser* barrelDispenser;
		//

		GameObjectContainer* gameObjectContainer;

		void initGame();

		void createFramerate();
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		

		void handleRound(ScreenManager& screenManager, int startAnotherRound);

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

		void handlePlayer(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleBarrels(CollisionManager* collisionManager, ScreenManager& screenManager, bool* quit, int* startAnotherRound);

		void handleCurrentRound(ScreenManager& screenManager, KeyboardManager& eventHandler, int* startAnotherRound);

		void handleCollisionWithKong(CollisionManager* collisionManager);
		void handleCollisionWithPrincess(CollisionManager* collisionManager);
		void handleCollisionWithBarrel(CollisionManager* collisionManager, DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
		void handleCollisionWithLadder(CollisionManager* collisionManager, int* flagLadder);

		void handleCollisionWithPlatform(CollisionManager* collisionManager, ScreenManager& screenManager, DynamicGameObject *gameObject, int* flagPlatform);
		void handleCollisionWithJumping();

		void drawElements(ScreenManager& screenManager);

		void closeGame();
		// void closeGame(ScreenManager& screenManager);


		// move to GameObjectManager

		void drawPlatforms(ScreenManager& screenManager);
};