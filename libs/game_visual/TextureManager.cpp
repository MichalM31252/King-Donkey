extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "TextureManager.h"

#include <stdio.h>
#include <string.h>
}

// rename

void TextureManager::loadTexture(const char* fileName) {
	sprite = SDL_LoadBMP(fileName);
	if (sprite == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		// this->closeGame(charset, screen, scrtex, window, renderer);
	}
}

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void TextureManager::drawSurface(SDL_Surface* screen, int x, int y) {
	SDL_Rect dest;
	dest.x = x - this->sprite->w / 2;
	dest.y = y - this->sprite->h / 2;
	dest.w = this->sprite->w;
	dest.h = this->sprite->h;
	SDL_BlitSurface(this->sprite, NULL, screen, &dest);
};