#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	
	#include "./SDL2-2.0.10/include/SDL.h"
	#include "./SDL2-2.0.10/include/SDL_main.h"

	#include "./libs/Constants.h"
	#include "./libs/game_gameplay/Game.h"
}




// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {


	Game game;

	game.initEverything();



	// zwolnienie powierzchni / freeing all surfaces
	return 0;
};
