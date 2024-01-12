#pragma once

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class ScreenManager {
	public:
		Uint32 black, green, red, blue, white;
		Uint32 ladderColor, platformColor;

		int rc;
		SDL_Surface* screen, * charset; // screen on which we will be drawing, charset is the bitmap with characters
		SDL_Surface* eti; // picture of eti
		SDL_Texture* scrtex; // ?? probably useless
		SDL_Window* window; // widnows window
		SDL_Renderer* renderer; // we send here to render the screen

		void SDLCheck();
		void SDLCreateWindowAndRenderer();
		void SDLSetHint();
		void SDLSetRenderLogicalSize();
		void SDLSetDefaultDrawColor();
		void SDLSetWindowTitle();
		void SDLSetCharset();
		void SDLSetScreen();
		void SDLSetTexture();
		
		void SDLSetEtiLogo();

		void SDLHideCursor();
		void SDLSetColorKey();

		void setColors();
		void drawOutlineOfTheBoard();
		void drawAdditionalInfo(double worldTime);
		void setUpSDL();

		void serveNextFrame();

		// don't touch for now you are sleepy
		void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
		void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
		void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
		void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
};