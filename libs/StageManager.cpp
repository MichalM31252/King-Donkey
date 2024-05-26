#pragma once

#include "StageManager.h"

StageManager::StageManager()
{

}

StageManager::StageManager(GameObjectContainer& gameObjectContainer)
{
	// assign gameObjectContainer to each one of these managers
	this->collisionManager = new CollisionManager(gameObjectContainer);
	this->screenManager = new ScreenManager();  // the program beaks here when you add gameObjectContainer
	this->gameObjectFactory = new GameObjectFactory();
	this->keyboardManager = new KeyboardManager();
}

