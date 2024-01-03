extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "TextureManager.h"
}

// rename

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer) {
	SDL_Surface* temporarySurface = SDL_LoadBMP(fileName); // IMG_Load(texture);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface); // this line swap??
	SDL_FreeSurface(temporarySurface);

	return texture;
}