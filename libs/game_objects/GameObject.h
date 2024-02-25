#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./TextureManager.h"
#include "../Constants.h"
}

class GameObject
{  
public:
	int xpos, ypos; // position of the game object
	SDL_Rect destRect, srcRect; // destRect is the physical representation of the game object // srcRect is whats going to be mapped onto the destRect
	TextureManager textureManager;
	char *tag[30]; // name of the object to differentiate between them barrel, player, ladder, etc

	GameObject(); // constructor
	void init(const char* fileName);
	void render(SDL_Surface* screen);
	void renderLadder(SDL_Surface* screen);
	void createSrcRect();
	void setSrcRect(int w, int h);
	void createDestRect();
	void setDestRect(int w, int h);
	void setPosition(int x, int y);
};

