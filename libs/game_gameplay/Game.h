#pragma once

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"
	#include "../game_visual/VisualHandler.h"
	#include "./EventHandler.h"
}

class Game {
	public:
		// logic
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		double distance, etiSpeed; // this can be used here

		// visual


		// Game(); Constructor NEEDED ADD DEFAULT VALUES
		void initGame();


		void setUpFramerate();
		void setUpGameObjects();
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		
		void setUpGame(VisualHandler& visualHandler);
		void handleGame(VisualHandler& visualHandler, EventHandler& eventHandler);

		void closeGame();
		void closeGame(VisualHandler& visualHandler);
};