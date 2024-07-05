#pragma once

#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectFactory.h"


class RoundManager {

	public:

	ScreenManager* screenManager;
	GameObjectFactory* gameObjectFactory;
	GameObjectContainer* gameObjectContainer;
	CollisionManager* collisionManager;

	RoundManager();
	RoundManager(ScreenManager* screenManager, GameObjectFactory* gameObjectFactory, GameObjectContainer* gameObjectContainer, CollisionManager* collisionManager);

	void handlePlayer();
	void handleBarrels(bool* quit, int* startAnotherRound);

	void handleRound(int startAnotherRound);
	void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);
	void decideWhichBoardToCreate(int startAnotherRound);
};