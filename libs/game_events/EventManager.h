#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
}

class EventManager {
public:
	void handleEvents(bool* quit, double deltaTime, Player* player);
private:
	SDL_Event event; // this can be used here
};