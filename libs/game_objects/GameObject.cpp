#include "GameObject.h"

#include "./TextureManager.h"
#include "../Constants.h"
// rename 

GameObject::GameObject()
{
	textureManager = TextureManager();
	SDL_Rect destRect = SDL_Rect();

	//srcRect.h = 32;
	//srcRect.w = 32;
	//srcRect.x = 0;
	//srcRect.y = 0;
}

void GameObject::update()
{
	// you need the dest rect for collision create a function that will get that info
	// update the position for example of the player or the barrel

	// this is handled by the DrawSurface function

	// this is how big the image is


	// hitbox
	//destRect.x = xpos;
	//destRect.y = ypos;
	// destRect.w = srcRect.w;
	// destRect.h = srcRect.h;
}

void GameObject::init(const char* fileName) {
	textureManager.loadTexture(fileName);
}

void GameObject::render(SDL_Surface* screen){
	textureManager.drawSurface(screen, xpos, ypos);
}

void GameObject::setUpSrcRect() {
	srcRect.w = textureManager.sprite->w;
	srcRect.h = textureManager.sprite->h;
}

void GameObject::setUpDestRect() {
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::setPosition(int x, int y) { // top left corner of the game object (hitbox) // change it to center so it will be easier to work with
	xpos = x;
	ypos = y;
	destRect.x = xpos;
	destRect.y = ypos;
}

