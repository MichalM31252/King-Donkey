#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class GameObject
{  
public:
	int xpos, ypos;
	SDL_Rect destRect, srcRect; // destRect is the physical representation of the game object // srcRect is whats going to be mapped onto the destRect
	SDL_Surface* sprite; // the image of the game object
	char *tag[30]; // name of the object to differentiate between them barrel, player, ladder, etc

	void createSrcRect();
	void createDestRect();
	void setSrcRect(int w, int h);
	void setDestRect(int w, int h);
	void setPosition(int x, int y);
};

