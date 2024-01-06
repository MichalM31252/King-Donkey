#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./TextureManager.h"
#include "../Constants.h"
}
// rename 

class GameObject
{  
public:
	int xpos, ypos; // position of the game object
	double xaccumulated, yaccumulated;
	SDL_Rect destRect, srcRect; // destRect is the physical representation of the game object // srcRect is whats going to be mapped onto the destRect
	TextureManager textureManager;
	char *tag[30]; // name of the object to differentiate between them barrel, player, ladder, etc

	GameObject(); // constructor
	void init(const char* fileName);
	void render(SDL_Surface* screen); // render the game object // for showing the game object // pass everything needed to show it
	void setUpSrcRect();
	void setUpDestRect();
	void setPosition(int x, int y);
private:
	
	// size of the gameObject rectangle
};

