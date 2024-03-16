
extern "C" {
#include "GameObject.h"
}

GameObject::GameObject()
{
	textureManager = TextureManager();
	SDL_Rect destRect = SDL_Rect();
}

void GameObject::init(const char* fileName) {
	textureManager.loadTexture(fileName);
}

void GameObject::render(SDL_Surface* screen){
	textureManager.drawSurface(screen, xpos, ypos);
}

void GameObject::renderLadder(SDL_Surface* screen) {
	textureManager.drawSurfaceLadder(screen, xpos, ypos, destRect);
}

void GameObject::createSrcRect() {
	srcRect.w = textureManager.sprite->w;
	srcRect.h = textureManager.sprite->h;
}

void GameObject::setSrcRect(int w, int h) {
	srcRect.w = w;
	srcRect.h = h;
}

void GameObject::createDestRect() {
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void GameObject::setDestRect(int w, int h) {
	destRect.w = w;
	destRect.h = h;
}

void GameObject::setPosition(int x, int y) { // top left corner of the game object (hitbox) // change it to center so it will be easier to work with
	xpos = x;
	ypos = y;
	destRect.x = xpos;
	destRect.y = ypos;
}

