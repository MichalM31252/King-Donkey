#pragma once

// rename

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class TextureManager {
public:
	void loadTexture(const char* fileName);
	void drawSurface(SDL_Surface* screen, int x, int y);
private:
	SDL_Surface* sprite;
	// this should be in TextureManager
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};