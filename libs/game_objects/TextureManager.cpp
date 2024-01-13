extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./TextureManager.h"
#include "../../libs/game_objects/GameObject.h"

#include <stdio.h>
#include <string.h>
}

// rename

void TextureManager::loadTexture(const char* fileName) {
	sprite = SDL_LoadBMP(fileName);
	if (sprite == NULL) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
		// closeGame(charset, screen, scrtex, window, renderer);
	}
}

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void TextureManager::drawSurface(SDL_Surface* screen, int xpos, int ypos) { // yeah there is the problem
	SDL_Rect dest;
	dest.x = xpos; // was dest.x = x - sprite->w / 2;
	dest.y = ypos; // was dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void TextureManager::drawSurfaceLadder(SDL_Surface* screen, int xpos, int ypos, SDL_Rect dest) { // not the best solution but works
	sprite->w = dest.w;
	sprite->h = dest.h;
	SDL_BlitSurface(sprite, NULL, screen, &dest); // it doesnt overwrite the original size of the image
};