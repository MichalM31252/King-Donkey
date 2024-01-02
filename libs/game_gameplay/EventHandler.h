#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class EventHandler {
public:
	void handleEvents(bool* quit);
private:
	SDL_Event event; // this can be used here
};