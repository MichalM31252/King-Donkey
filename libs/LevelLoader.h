#pragma once

#include "PhysicsManager.h"
#include "CollisionResolver.h"
#include "GameObjectContainer.h"
#include "Gorilla.h"

class LevelLoader {
public:
	GameObjectContainer* gameObjectContainer;

	LevelLoader() = default;
	explicit LevelLoader(GameObjectContainer* gameObjectContainer);

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

	void decideWhichBoardToCreate(int startAnotherRound);
};