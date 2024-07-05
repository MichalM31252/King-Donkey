#include "RoundManager.h"

RoundManager::RoundManager() {
	screenManager = new ScreenManager();
	gameObjectFactory = new GameObjectFactory();
	gameObjectContainer = new GameObjectContainer();
	collisionManager = new CollisionManager(gameObjectContainer);
}

RoundManager::RoundManager(ScreenManager* screenManager, GameObjectFactory* gameObjectFactory, GameObjectContainer* gameObjectContainer, CollisionManager* collisionManager) {
	this->screenManager = screenManager;
	this->gameObjectFactory = gameObjectFactory;
	this->gameObjectContainer = gameObjectContainer;
	this->collisionManager = collisionManager;
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

		handlePlayer(); // player collision
		handleBarrels(&quit, startAnotherRound); // barrel collision

		gameObjectContainer->player->update(screenManager->deltaTime);
		// maybe also update the barrels here ???

		// this is for keyboard events // should be changed
		eventHandler.handleEvents(&quit, screenManager->deltaTime, gameObjectContainer->player, startAnotherRound);
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

// MOVE TO GAME OBJECT MANAGER
void RoundManager::handlePlayer() { // player collision

	Player* player = gameObjectContainer->player;

	int isPlayerInsidePlatform = 0;

	collisionManager->handleCollisionWithPlatform(gameObjectContainer->player, &isPlayerInsidePlatform);
	collisionManager->handlePlayerCollisionWithKong();
	collisionManager->handlePlayerCollisionWithPrincess();
	collisionManager->handlePlayerCollisionWithLadder();

	if (!player->isClimbing) {
		if (isPlayerInsidePlatform) {
			screenManager->loadTexture(player, PLAYER_1_FILENAME);
			collisionManager->handleCollisionWithJumping();
		}
		else {
			// again start falling not handle falling
			PhysicsManager::handleFalling(player, screenManager->deltaTime);
		}
		if (player->isJumping) { // handle jumping
			player->jump(screenManager->deltaTime);
		}
	}

	if (player->isJumping && player->ypos <= player->jumpHeightStop) {
		player->stopJumping();
		player->startFalling();
	}
}

// MOVE TO GAME OBJECT MANAGER
void RoundManager::handleBarrels(bool* quit, int* startAnotherRound) {
	gameObjectContainer->barrelDispenser->updateBarrelDispenser(screenManager->deltaTime);

	for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {

		DynamicGameObject* barrel = &gameObjectContainer->barrelDispenser->barrelHolder->barrels[i];

		collisionManager->handlePlayerCollisionWithBarrel(barrel, quit, startAnotherRound);

		int isGameObjectInsidePlatform = 0;
		collisionManager->handleCollisionWithPlatform(barrel, &isGameObjectInsidePlatform);

		if (isGameObjectInsidePlatform) {
			if ((*barrel).isFalling) {
				// stopObjectFromFallingThroughPlatform
				(*barrel).stopFalling();
				(*barrel).stopMove();
			}
			(*barrel).moveStart(DEFAULT_BARREL_SPEED);
			(*barrel).startMovingRight(screenManager->deltaTime);
		}
		else {
			// idk but shououldnt this be renamed to start falling?
			PhysicsManager::handleFalling(barrel, screenManager->deltaTime); // THE PROBLEM IS HERE
		}
		(*barrel).update(screenManager->deltaTime);
	}
}
