#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
#include "EventManager.h"
#include "../Constants.h"
}

void EventManager::handleEvents(bool* quit, double deltaTime, Player* player, int *startAnotherRound) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: // event of pressing down a key on keyboard
				player->moveStart();
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						*quit = true; // Esc = Quit CLOSING THE PROGRAM HERE
						break;
					case SDLK_UP: // this should be start moving and not moving 
						if (player->isInsideLadder) {
							player->isClimbing = true;

							player->startMovingUp(deltaTime);
						}
						// check collision with ladder
						// if yes:
						// isClimbing = true;
						// if 1px below player is platform then :
						// player->isClimbing = false;
						break;
					case SDLK_LEFT: // this should be start moving
						if (!player->isClimbing) {
							player->startMovingLeft(deltaTime);
						}
						break;
					case SDLK_RIGHT: // this should be start moving
						if (!player->isClimbing) {
							player->startMovingRight(deltaTime);
						}
						break;
					case SDLK_DOWN: // this should be start moving
						if (player->isInsideLadder) {
							player->isClimbing = true;

							player->startMovingDown(deltaTime);
						}

						// do not add is climbing false when key down because the player will start falling when keys are not pressed

						break;
					case SDLK_n:
						*startAnotherRound = 1;
						*quit = true;
						break;
				}
				break;
			case SDL_KEYUP: // similarly event when you stop pressing
				player->moveStop();
				break;
			case SDL_QUIT: // This is for closing the window by the regular "X" button
				*quit = true;
				break;
		}
	}
}