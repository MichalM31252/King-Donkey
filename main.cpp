#define _USE_MATH_DEFINES

extern "C" {
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
