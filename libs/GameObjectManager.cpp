extern "C" {
#include "./GameObjectManager.h"
}

GameObjectManager::GameObjectManager() {
	GameObjectContainer* ga = new GameObjectContainer();
	gameObjectContainer = ga;
}

GameObjectManager::~GameObjectManager() {

}