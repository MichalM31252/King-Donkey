#include "GameObject.h"

#include "../../libs/game_visual/TextureManager.h"
#include "../../libs/Constants.h"
// rename 

GameObject::GameObject()
{
	textureManager = TextureManager();
	SDL_Rect destRect = SDL_Rect();
	objectSpeed = 0;
	xpos = 0;
	ypos = 0;
}

void GameObject::update()
{
	// you need the dest rect for collision create a function that will get that info
	// update the position for example of the player or the barrel

	// this is handled by the DrawSurface function

	// this is how big the image is
	//srcRect.h = 32; 
	//srcRect.w = 32;
	//srcRect.x = 0;
	//srcRect.y = 0;

	// most likely the hitbox
	//destRect.x = xpos;
	//destRect.y = ypos;
	//destRect.w = srcRect.w * 2;
	//destRect.h = srcRect.h * 2;
}

void GameObject::init(const char* fileName) {
	textureManager.loadTexture(fileName);
}

void GameObject::render(SDL_Surface* screen){
	textureManager.drawSurface(screen,xpos,ypos);
}

void GameObject::setUpDestRect() {
	// most likely the hitbox
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = textureManager.sprite->w;
	destRect.h = textureManager.sprite->h;
}

void GameObject::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void GameObject::moveLeft(double deltaTime) {
	objectSpeed = DEFAULT_PLAYER_SPEED;
	xpos -= deltaTime * objectSpeed;
	destRect.x = xpos;
}

void GameObject::moveRight(double deltaTime) {
	objectSpeed = DEFAULT_PLAYER_SPEED;
	xpos += deltaTime * objectSpeed;
	destRect.x = xpos;
}

void GameObject::moveUp(double deltaTime) {
	// under the circumstance that a player is on the ladder
	objectSpeed = DEFAULT_PLAYER_SPEED;
	ypos -= deltaTime * objectSpeed;
	destRect.y = ypos;
}

void GameObject::moveDown(double deltaTime) {
	// under the circumstance that a player is on the ladder
	objectSpeed = DEFAULT_PLAYER_SPEED;
	ypos += deltaTime * objectSpeed;
	destRect.y = ypos;
}

void GameObject::moveStop() {
	objectSpeed = 0;
}