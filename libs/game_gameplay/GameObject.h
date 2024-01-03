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
	GameObject(int x, int y, int objectSpeed); // constructor
	void init(const char* fileName);
	void update(); // update the game object // for moving for example
	void render(SDL_Surface* screen); // render the game object // for showing the game object // pass everything needed to show it

private:
	int xpos, ypos, objectSpeed;
	TextureManager textureManager;
	// size of the gameObject rectangle
};

