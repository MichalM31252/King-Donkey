#pragma once

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
}

// rename 

class GameObject
{
public:
	GameObject(const char* texture, SDL_Renderer* renderer); // constructor
	~GameObject(); // desctructor
	void update(); // update the game object
	void render(); // render the game object

private:
	int xpos, ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
};

