#pragma once

#include "PhysicsManager.h"
#include "CollisionResolver.h"
#include "GameObjectContainer.h"
#include "Gorilla.h"

class LevelLoader {
public:
	std::shared_ptr<GameObjectContainer> gameObjectContainer;

	LevelLoader() = default;
	explicit LevelLoader(std::shared_ptr<GameObjectContainer> container);

	void createPlayer();
	void createDonkeyKong();
	void createPrincess();

	void createPlatforms1();
	void createLadders1();

	// void createPlatforms2();
	void createLadders2();

	// void createPlatforms3();
	void createLadders3();

	void loadLevel1();
	void loadLevel2();
	void loadLevel3();
};