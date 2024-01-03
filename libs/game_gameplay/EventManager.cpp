#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "EventManager.h"
	#include "../Constants.h"
}

void EventManager::handleEvents(bool *quit) {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN: // event of pressing down a key on keyboard
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					*quit = true; // Esc = Quit CLOSING THE PROGRAM HERE
				} 			
				else if (event.key.keysym.sym == SDLK_UP) {
					// 
					// Speed = 2.0; // Arrow Up Fly faster by changing speed
				} 
				else if (event.key.keysym.sym == SDLK_DOWN) {
					// etiSpeed = 0.3; // Reduce the speed
				}
				break;
			case SDL_KEYUP: // similarly event when you stop pressing
				// etiSpeed = 1.0; // reset the speed of ETI
				break;
			case SDL_QUIT: // This is for closing the window by the regular "X" button
				*quit = true;
				break;
		}
	}
}