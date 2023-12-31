#pragma once

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class VisualHandler {
	public:
		Uint32 black;
		Uint32 green;
		Uint32 red;
		Uint32 blue;
		Uint32 white;
		Uint32 ladderColor;
		Uint32 platformColor; // just draw a line instead of a big platform

		void setColors(SDL_Surface* screen);

		void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
		void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
		void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
		void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
		void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	
};