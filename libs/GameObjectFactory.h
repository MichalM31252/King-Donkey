#pragma once
#include "PhysicsManager.h"
#include "CollisionResolver.h"
#include "GameObjectContainer.h"

class GameObjectFactory {
public:
	GameObjectContainer* gameObjectContainer;
	CollisionResolver* collisionResolver;

	GameObjectFactory();
	GameObjectFactory(GameObjectContainer* gameObjectContainer);

	void createPlayer();
	void createDonkeyKong();
	void createPrincess();

	void createPlatforms1();
	void createLadders1();
	void createPlatforms2();
	void createLadders2();
	void createPlatforms3();
	void createLadders3();
	void createBarrels();

	void createBoard(int boardId);

	~GameObjectFactory();
};