extern "C" {
#include "./GameObjectManager.h"
}

GameObjectManager::GameObjectManager() {
	GameObjectContainer* ga = new GameObjectContainer();
	gameObjectContainer = ga;

	CollisionManager* collisionM = new CollisionManager();
	collisionManager = collisionM;
}

GameObjectManager::~GameObjectManager() {

}