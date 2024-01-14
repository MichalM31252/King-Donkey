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
}

class Game {
	public:
		// logic
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		GameObject *donkeyKong;
		GameObject *princess;
		Player* player;
		PlatformHolder* platformHolder;
		LadderHolder* ladderHolder;


		// Game(); Constructor NEEDED ADD DEFAULT VALUES
		void initGame();

		void setUpFramerate();
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		

		void handleRound(ScreenManager& screenManager, int startAnotherRound);

		void setUpBoard(int boardId);

		void setUpPlayer();
		void setUpDonkeyKong();
		void setUpPrincess();

		void setUpPlatforms1();
		void setUpLadders1();

		void setUpPlatforms2();
		void setUpLadders2();

		void setUpPlatforms3();
		void setUpLadders3();

		void handleCurrentRound(ScreenManager& screenManager, EventManager& eventHandler, int* startAnotherRound);


		void handleCollisionWithKong(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleCollisionWithPrincess(CollisionManager* collisionManager, ScreenManager& screenManager);
		void handleCollisionWithLadder(CollisionManager* collisionManager, ScreenManager& screenManager, int* flagLadder);
		void handleCollisionWithPlatform(CollisionManager* collisionManager, ScreenManager& screenManager, DynamicGameObject *gameObject, int* flagPlatform);
		void handleCollisionWithJumping();
		void handleFalling();
		void handleJumping();


		void closeGame();
		void closeGame(ScreenManager& screenManager);
};