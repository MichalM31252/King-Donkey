#pragma once

#include <math.h>
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class Platform {
public:
	int x1pos; 
	int y1pos;
	int x2pos;
	int y2pos;

	double a;
	double b;
	double c;

	void setPosition(int x1, int y1, int x2, int y2);
};