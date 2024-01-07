#pragma once

extern "C" {
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "./Constants.h"
}
// rename 

class Platform
{
public:
	int x1pos, y1pos, x2pos, y2pos; // first platform line
	double a1, b1, c1;
	int x3pos, y3pos, x4pos, y4pos; // second line to fill in the blanks to make sure nothing passes
	double a2, b2, c2;

	char* tag[30];
	void setPosition(int x1, int y1, int x2, int y2);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void setEquationLine();
	void render(SDL_Surface* screen);
};

