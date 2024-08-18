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

	return 0;
};
