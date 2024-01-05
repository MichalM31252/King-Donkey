#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../game_visual/TextureManager.h"
#include "../Constants.h"
}
// rename 

class GameObject
{  
public:

	SDL_Rect destRect;

	GameObject(); // constructor
	void init(const char* fileName);
	void update(); // update the game object // for moving for example
	void render(SDL_Surface* screen); // render the game object // for showing the game object // pass everything needed to show it
	void setUpDestRect();
	void setPosition(int x, int y);
private:
	TextureManager textureManager;
	// size of the gameObject rectangle
};

