#define _USE_MATH_DEFINES


extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>
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
				player->moveStart(DEFAULT_PLAYER_SPEED);
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						*quit = true; // Esc = Quit CLOSING THE PROGRAM HERE
						*startAnotherRound = 0;
						break;
					case SDLK_UP: // why is he still in the ladder 
						onKeyUp(deltaTime, player);	
						break;
					case SDLK_LEFT:
						if (!player->isClimbing) {
							player->startMovingLeft(deltaTime);
						}
						break;
					case SDLK_RIGHT:
						if (!player->isClimbing) {
							player->startMovingRight(deltaTime);
						}
						break;
					case SDLK_DOWN:
						if (player->isInsideLadder) {
							player->isClimbing = true;
							player->textureManager.loadTexture(PLAYER_CLIMB);
							player->startMovingDown(deltaTime);
						}
						break;
					case SDLK_SPACE:
						player->initJump();
						break;
					case SDLK_n:
						*startAnotherRound = 1;
						*quit = true;
						break;
					case SDLK_1: // load level 1
						*startAnotherRound = 1;
						*quit = true;
						break;
					case SDLK_2: // load level 2
						*startAnotherRound = 2;
						*quit = true;
						break;
					case SDLK_3: // load level 3
						*startAnotherRound = 3;
						*quit = true;
						break;
				}
				break;
			case SDL_KEYUP: // similarly event when you stop pressing
				player->stopMove();
				break;
			case SDL_QUIT: // This is for closing the window by the regular "X" button
				*quit = true;
				*startAnotherRound = 0;
				break;
		}
	}
}

void EventManager::onKeyUp(double deltaTime, Player* player) {
	if (player->isInsideLadder) {
		player->isClimbing = true; // the problem is most likely with this 
		player->textureManager.loadTexture(PLAYER_CLIMB);
		player->startMovingUp(deltaTime);
	}
}