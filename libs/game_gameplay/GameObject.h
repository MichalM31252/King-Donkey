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
	void moveLeft(double delta); 
	void moveRight(double delta);
	void moveUp(double delta); 
	void moveDown(double delta);
	void moveStop();
private:
	int xpos, ypos;
	double objectSpeed;
	TextureManager textureManager;
	
	// size of the gameObject rectangle
};

