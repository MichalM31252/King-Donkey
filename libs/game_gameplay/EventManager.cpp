#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../../libs/game_gameplay/GameObject.h"
#include "EventManager.h"
#include "../Constants.h"
}

void EventManager::handleEvents(bool* quit, double deltaTime, GameObject* player) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: // event of pressing down a key on keyboard
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					*quit = true; // Esc = Quit CLOSING THE PROGRAM HERE
				} 			
				else if (event.key.keysym.sym == SDLK_UP) {
					player->moveUp(deltaTime);
					// Speed = 2.0; // Arrow Up Fly faster by changing speed
				} 
				else if (event.key.keysym.sym == SDLK_LEFT) {
					player->moveLeft(deltaTime);
					// Speed = 2.0; // Arrow Up Fly faster by changing speed
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					player->moveRight(deltaTime);
					// Speed = 2.0; // Arrow Up Fly faster by changing speed
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					player->moveDown(deltaTime);
					// etiSpeed = 0.3; // Reduce the speed
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