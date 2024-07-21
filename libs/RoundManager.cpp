#include "RoundManager.h"

RoundManager::RoundManager() {
	screenManager = new ScreenManager();
	gameObjectFactory = new GameObjectFactory();
	gameObjectContainer = new GameObjectContainer();
	collisionResolver = new CollisionResolver(gameObjectContainer, screenManager);
}

RoundManager::RoundManager(ScreenManager* screenManager, GameObjectFactory* gameObjectFactory, GameObjectContainer* gameObjectContainer, CollisionResolver* collisionResolver) {
	this->screenManager = screenManager;
	this->gameObjectFactory = gameObjectFactory;
	this->gameObjectContainer = gameObjectContainer;
	this->collisionResolver = collisionResolver;
}

// MOVE TO ROUND MANAGER
void RoundManager::handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound) {
	bool quit = false;
	while (!quit) {
		screenManager->handleDifferentComputers();
		screenManager->updateWorldTime();
		screenManager->handleFPSTimer();
		screenManager->drawOutlineOfTheBoard();
		screenManager->drawAdditionalInfo();
		screenManager->drawElements();
		screenManager->serveNextFrame();
		screenManager->frames++;

		eventHandler.handleEvents(&quit, screenManager->deltaTime, gameObjectContainer->player, startAnotherRound);

		gameObjectContainer->player->update(screenManager->deltaTime);
		collisionResolver->handlePlayerCollision();
		screenManager->handlePlayerSprite(gameObjectContainer->player);

		gameObjectContainer->barrelDispenser->update(screenManager->deltaTime);

		for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {
			DynamicGameObject* barrel = &gameObjectContainer->barrelDispenser->barrelHolder->barrels[i];
			(*barrel).update(screenManager->deltaTime);
			// update sprite of barrel here
		}

		collisionResolver->handleBarrelsCollision(&quit, startAnotherRound);

		// maybe also update the barrels here ???
	};
}
// MOVE TO ROUND MANAGER
void RoundManager::handleRound(int startAnotherRound) {
	KeyboardManager eventHandler;
	screenManager->createFramerate();

	decideWhichBoardToCreate(startAnotherRound);
	handleCurrentRound(eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(startAnotherRound);
	}
}

void RoundManager::decideWhichBoardToCreate(int startAnotherRound) {
	if (startAnotherRound) {
		if (startAnotherRound == BOARD_ID_A) {
			gameObjectFactory->createBoard(BOARD_ID_A);
		}
		if (startAnotherRound == BOARD_ID_B) {
			gameObjectFactory->createBoard(BOARD_ID_B);
		}
		if (startAnotherRound == BOARD_ID_C) {
			gameObjectFactory->createBoard(BOARD_ID_C);
		}
	}
	else {
		gameObjectFactory->createBoard(BOARD_ID_A);
	}
}
