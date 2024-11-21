#pragma once
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class GameTime {
public:
	int tick1;
	int tick2;
	double deltaTime;
	double worldTime;
	bool isPaused;

	GameTime();
	void start();
	void update();
	void reset();
	void pause();
	void resume();
};

