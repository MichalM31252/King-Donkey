#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../game_visual/VisualManager.h"
#include "../game_gameplay/GameObject.h"
#include "./EventManager.h"
}

class Game {
	public:
		// logic
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		GameObject* player;
		// visual

		// Game(); Constructor NEEDED ADD DEFAULT VALUES
		void initGame();

		void setUpFramerate();
		void setUpGameObjects(SDL_Surface* screen);
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		
		void setUpGame(VisualManager& visualManager);
		void handleGame(VisualManager& visualManager, EventManager& eventManager);

		void closeGame();
		void closeGame(VisualManager& visualManager);
};