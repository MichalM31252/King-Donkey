#include "GameObject.h"

#include "../../libs/game_visual/TextureManager.h"
// rename 

GameObject::GameObject(int x, int y, int speed)
{
	// x pos 
	// y pos 

	this->xpos = x; // position of the gameObject
	this->ypos = y;
	this->objectSpeed = speed;
	// texture (path) gameObject or texture manager, 
	// nah game object should get the texture and pass it to the texture manager
	// for now the texture manager is not need but it will be needed in the future for animations so use it 
	
	// this class needs the renderer and the screen to actually place anything on the screen 
	// nah that should be done using the TextureManager


}

void GameObject::update()
{
	// you need the dest rect for collision create a function that will get that info
	// update the position for example of the player or the barrel

	// this is handled by the DrawSurface function
	//srcRect.h = 32;
	//srcRect.w = 32;
	//srcRect.x = 0;
	//srcRect.y = 0;

	//destRect.x = xpos;
	//destRect.y = ypos;
	//destRect.w = srcRect.w * 2;
	//destRect.h = srcRect.h * 2;
}

void GameObject::init(const char* fileName) {
	textureManager.loadTexture(fileName);
}

void GameObject::render(SDL_Surface* screen){
	this->textureManager.drawSurface(screen,this->xpos,this->ypos);
}