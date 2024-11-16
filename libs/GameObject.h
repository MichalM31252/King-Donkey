#pragma once
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class GameObject {
public:
	int xpos;
	int ypos;
	SDL_Rect destRect;
	SDL_Rect srcRect; // destRect is the physical representation of the game object // srcRect is whats going to be mapped onto the destRect
	SDL_Surface* sprite; // the image of the game object

	void createSrcRect();
	void createDestRect();
	void setSrcRect(int w, int h);
	void setDestRect(int w, int h);
	void setPosition(int x, int y);
};

