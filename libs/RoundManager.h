#pragma once

#include "KeyboardManager.h"
#include "ScreenManager.h"
#include "GameObjectFactory.h"


class RoundManager {

	public:

	ScreenManager* screenManager;
	GameObjectFactory* gameObjectFactory;
	GameObjectContainer* gameObjectContainer;
	CollisionResolver* collisionResolver;

	RoundManager();
	RoundManager(ScreenManager* screenManager, GameObjectFactory* gameObjectFactory, GameObjectContainer* gameObjectContainer, CollisionResolver* collisionResolver);

	void handleRound(int startAnotherRound);
	void handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound);
	void decideWhichBoardToCreate(int startAnotherRound);
};