#define _USE_MATH_DEFINES

extern "C" {
#include "Game.h"
#include "CollisionManager.h" // temporary fix
}

Game::Game() {
	GameObjectContainer* gameObjectC = new GameObjectContainer();
	gameObjectContainer = gameObjectC;

	ScreenManager* screenMan = new ScreenManager();
	screenManager = screenMan;

	GameObjectFactory* gameObjectMan = new GameObjectFactory(gameObjectContainer);
	gameObjectFactory = gameObjectMan;

	CollisionManager* collisionMan = new CollisionManager(gameObjectContainer);
	collisionManager = collisionMan;
}

// MOVE TO ROUND MANAGER
void Game::handleCurrentRound(KeyboardManager& eventHandler, int *startAnotherRound) {
	bool quit = false;
	while (!quit) {

		screenManager->handleDifferentComputers();
		screenManager->updateWorldTime();
		screenManager->handleFPSTimer();

		screenManager->drawOutlineOfTheBoard();
		screenManager->drawAdditionalInfo(screenManager->worldTime);

		handlePlayer(); // player collision
		handleBarrels(&quit, startAnotherRound); // barrel collision

		gameObjectFactory->gameObjectContainer->player->update(screenManager->deltaTime);

		drawElements();

		screenManager->serveNextFrame();

		eventHandler.handleEvents(&quit, screenManager->deltaTime, gameObjectFactory->gameObjectContainer->player, startAnotherRound);

		screenManager->frames++;
	};
}

// MOVE TO ROUND MANAGER
void Game::handleRound(int startAnotherRound) {
	KeyboardManager eventHandler;
	screenManager->createFramerate();
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

	handleCurrentRound(eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(startAnotherRound);
	}
}

void Game::initGame() {
	screenManager->createSDL();

	int startAnotherRound = 0;
	handleRound(startAnotherRound);

	closeGame();
}

// MOVE TO TEXTURE MANAGER
void Game::drawPlatforms() {
	for (int i = 0; i < gameObjectFactory->gameObjectContainer->platformHolder->numberOfElements; i++) {
		gameObjectFactory->gameObjectContainer->platformHolder->platforms[i].render(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawLadders() {
	for (int i = 0; i < gameObjectFactory->gameObjectContainer->ladderHolder->numberOfElements; i++) {
		screenManager->renderLadder(&gameObjectFactory->gameObjectContainer->ladderHolder->ladders[i], screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawBarrels() {
	for (int i = 0; i < gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {
		screenManager->renderGameObject(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawElements() { // don't repeat yourself
	screenManager->renderGameObject(gameObjectFactory->gameObjectContainer->donkeyKong, screenManager->screen);
	screenManager->renderGameObject(gameObjectFactory->gameObjectContainer->princess, screenManager->screen);
	screenManager->renderGameObject(gameObjectFactory->gameObjectContainer->player, screenManager->screen);

	drawPlatforms();
	drawLadders();
	drawBarrels();
}

// MOVE TO GAME OBJECT MANAGER
void Game::handlePlayer() { // player collision
	collisionManager->handleCollisionWithKong();
	collisionManager->handleCollisionWithPrincess();
	int flagLadder = 0;
	collisionManager->handleCollisionWithLadder(&flagLadder);
	int flagPlatform = 0;
	collisionManager->handleCollisionWithPlatform(gameObjectFactory->gameObjectContainer->player, &flagPlatform);

	if (!gameObjectFactory->gameObjectContainer->player->isClimbing) {
		if (flagPlatform) {
			screenManager->loadTexture(gameObjectFactory->gameObjectContainer->player, PLAYER_1_FILENAME);
			collisionManager->handleCollisionWithJumping();
		}
		else {
			PhysicsManager::handleFalling(gameObjectFactory->gameObjectContainer->player, screenManager->deltaTime);
		}
		if (gameObjectFactory->gameObjectContainer->player->isJumping) { // handle jumping
			gameObjectFactory->gameObjectContainer->player->jump(screenManager->deltaTime);
		}
	}

	if (gameObjectFactory->gameObjectContainer->player->isJumping && gameObjectFactory->gameObjectContainer->player->ypos <= gameObjectFactory->gameObjectContainer->player->jumpHeightStop) {
		gameObjectFactory->gameObjectContainer->player->stopJumping();
		gameObjectFactory->gameObjectContainer->player->startFalling();
	}
}

// MOVE TO GAME OBJECT MANAGER
void Game::handleBarrels(bool* quit, int* startAnotherRound) {
	gameObjectFactory->gameObjectContainer->barrelDispenser->updateBarrelDispenser(screenManager->deltaTime);

	for (int i = 0; i < gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {

		collisionManager->handleCollisionWithBarrel(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], quit, startAnotherRound);

		int flagPlatform = 0;
		collisionManager->handleCollisionWithPlatform(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], &flagPlatform);

		if (flagPlatform) {
			if (gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].isFalling) {
				gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopFalling();
				gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopMove();
			}
			gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].moveStart(DEFAULT_BARREL_SPEED);
			gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].startMovingRight(screenManager->deltaTime);
		}
		else {
			PhysicsManager::handleFalling(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], screenManager->deltaTime); // THE PROBLEM IS HERE
		}
		gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].update(screenManager->deltaTime);
	}
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

// Implement this in the future
//void Game::closeGame(ScreenManager& screenManager) { // change this into a vector to be more efficient (so it can destroy every gameobject)
//	SDL_FreeSurface(screenManager.charset);
//	SDL_FreeSurface(screenManager.screen);
//	SDL_DestroyTexture(screenManager.scrtex);
//	SDL_DestroyWindow(screenManager.window);
//	SDL_DestroyRenderer(screenManager.renderer);
//	SDL_Quit();
//	exit(0);
//}
