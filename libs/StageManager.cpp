#pragma once

#include "StageManager.h"

StageManager::StageManager(){

}

StageManager::StageManager(GameObjectContainer* gameObjectContainer){ // assign gameObjectContainer to each one of these managers

	this->screenManager = new ScreenManager();  // the program breaks here when you add gameObjectContainer

	this->collisionManager = new CollisionManager(gameObjectContainer);
	this->gameObjectFactory = new GameObjectFactory(gameObjectContainer);
	this->keyboardManager = new KeyboardManager(gameObjectContainer);

	// physics manager is entirely static
	// round manager doesnt exist yet

}

