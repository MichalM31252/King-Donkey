#pragma once
#include "./PhysicsManager.h"
#include "./game_events/CollisionManager.h"
#include "./game_objects/TextureManager.h"
#include "./GameObjectContainer.h"

class GameObjectManager {
public:
	GameObjectContainer* gameObjectContainer;
	CollisionManager* collisionManager;
	TextureManager* textureManager;

	PhysicsManager* physicsManager; // this only holds a static method so it doesn't need to be a pointer and it doesn't need to be here

	GameObjectManager();

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

	~GameObjectManager();
};