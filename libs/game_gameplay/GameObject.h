#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../game_visual/TextureManager.h"
}
// rename 

class GameObject
{  
public:
	GameObject(int x, int y, double objectSpeed); // constructor
	void init(const char* fileName);
	void update(); // update the game object // for moving for example
	void render(SDL_Surface* screen); // render the game object // for showing the game object // pass everything needed to show it
	void moveLeft(double delta); // -1 up, 1 is down
	void moveRight(double delta); // -1 up, 1 is down
	void moveUp(double delta); // -1 left, 1 right
	void moveDown(double delta); // -1 left, 1 right
	void moveStop();
private:
	int xpos, ypos;
	double objectSpeed;
	TextureManager textureManager;
	// size of the gameObject rectangle
};

