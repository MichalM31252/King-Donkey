#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../../libs/game_gameplay/GameObject.h"
}

class EventManager {
public:
	void handleEvents(bool* quit, double deltaTime, GameObject* player);
private:
	SDL_Event event; // this can be used here
};