#pragma once

#include "StageManager.h"

StageManager::StageManager()
{

}

StageManager::StageManager(GameObjectContainer& gameObjectContainer)
{
	// assign gameObjectContainer to each one of these managers
	this->collisionManager = new CollisionManager();
	this->screenManager = new ScreenManager();
	this->collisionManager = new CollisionManager();
	this->gameObjectFactory = new GameObjectFactory();
	this->keyboardManager = new KeyboardManager();
}

StageManager::~StageManager()
{

}
