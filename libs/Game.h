#pragma once

extern "C" {
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "./game_screen/ScreenManager.h"
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "./game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
#include "./game_events/EventManager.h"
#include "./game_events/CollisionManager.h"
#include "./Platform.h"
#include "./PlatformHolder.h"
#include "./LadderHolder.h"
#include "./BarrelHolder.h"
#include "./BarrelDispenser.h"
}

class Game {
	public:
		
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		GameObject *donkeyKong;
		GameObject *princess;
		Player* player;
		PlatformHolder* platformHolder;
		LadderHolder* ladderHolder;
		BarrelDispenser* barrelDispenser;
	
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

		void handlePlayer(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleBarrels(CollisionManager* collisionManager, ScreenManager& screenManager, bool* quit, int* startAnotherRound);

		void handleCurrentRound(ScreenManager& screenManager, EventManager& eventHandler, int* startAnotherRound);


		void handleCollisionWithKong(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleCollisionWithPrincess(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleCollisionWithBarrel(CollisionManager* collisionManager, ScreenManager& screenManager, DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
		void handleCollisionWithLadder(CollisionManager* collisionManager, ScreenManager& screenManager, int* flagLadder);
		void handleCollisionWithPlatform(CollisionManager* collisionManager, ScreenManager& screenManager, DynamicGameObject *gameObject, int* flagPlatform);
		void handleCollisionWithJumping();
		void handleFalling(DynamicGameObject* dynamicGameObject);
		void handleJumping();

		void drawElements(ScreenManager& screenManager);

		void closeGame();
		void closeGame(ScreenManager& screenManager);
};