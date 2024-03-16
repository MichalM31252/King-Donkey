#pragma once

extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"

#include "../game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
#include "../Constants.h"
}

class EventManager {
public:
	void handleEvents(bool* quit, double deltaTime, Player* player, int* startAnotherRound);

	void onKeyDown(bool* quit, double deltaTime, Player* player, int* startAnotherRound);
	void onKeyUp(Player* player);

	void initializeQuit(bool* quit, int* startAnotherRound);
	void onKeyPressArrowUp(double deltaTime, Player* player);
	void onKeyPressArrowLeft(double deltaTime, Player* player);
	void onKeyPressArrowRight(double deltaTime, Player* player);
	void onKeyPressArrowDown(double deltaTime, Player* player);
	void onKeyPressSpace(Player* player);
	void onKeyPressN(bool* quit, int* startAnotherRound);
	void onKeyPress1(bool* quit, int* startAnotherRound);
	void onKeyPress2(bool* quit, int* startAnotherRound);
	void onKeyPress3(bool* quit, int* startAnotherRound);
	
private:
	SDL_Event event; // this can be used here
};