#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../../libs/game_gameplay/GameObject.h"
#include "../../libs/game_gameplay/DynamicGameObject.h"
#include "EventManager.h"
#include "../Constants.h"
}

void EventManager::handleEvents(bool* quit, double deltaTime, DynamicGameObject* player) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: // event of pressing down a key on keyboard
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						*quit = true; // Esc = Quit CLOSING THE PROGRAM HERE
						break;
					case SDLK_UP:
						player->moveUp(deltaTime);
						break;
					case SDLK_LEFT:
						player->moveLeft(deltaTime);
						break;
					case SDLK_RIGHT:
						player->moveRight(deltaTime);
						break;
					case SDLK_DOWN:
						player->moveDown(deltaTime);
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