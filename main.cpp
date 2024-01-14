#define _USE_MATH_DEFINES

extern "C" {
	#include <math.h>
	#include <stdio.h>
	#include <string.h>
	#include "./SDL2-2.0.10/include/SDL.h"
	#include "./SDL2-2.0.10/include/SDL_main.h"

	#include "./libs/Game.h"
}

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	Game game;

	game.initGame();

	// zwolnienie powierzchni / freeing all surfaces
	return 0;
};
