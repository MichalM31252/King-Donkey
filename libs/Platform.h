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
	double a, b, c;

	char* tag[30];
	void setPosition(int x1, int y1, int x2, int y2);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void render(SDL_Surface* screen);
};

