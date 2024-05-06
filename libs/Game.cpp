#define _USE_MATH_DEFINES

extern "C" {
#include "./Game.h"
}

Game::Game() {
	ScreenManager* screenMan = new ScreenManager();
	screenManager = screenMan;

	GameObjectFactory* gameObjectMan = new GameObjectFactory();
	gameObjectFactory = gameObjectMan;
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

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithKong() {
	if (gameObjectFactory->collisionManager->isCollisionBetweenRects(gameObjectFactory->gameObjectContainer->player->destRect, gameObjectFactory->gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPrincess() {
	if (gameObjectFactory->collisionManager->isCollisionBetweenRects(gameObjectFactory->gameObjectContainer->player->destRect, gameObjectFactory->gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (gameObjectFactory->collisionManager->isCollisionBetweenRects(gameObjectFactory->gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithLadder(int* flagLadder) {
	for (int i = 0; i < gameObjectFactory->gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (gameObjectFactory->collisionManager->isRectInsideLadder(gameObjectFactory->gameObjectContainer->player->destRect, gameObjectFactory->gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			*flagLadder = 1;
		}
	}
	if (*flagLadder) {
		gameObjectFactory->gameObjectContainer->player->isInsideLadder = true;
	}
	else {
		gameObjectFactory->gameObjectContainer->player->isInsideLadder = false;
		gameObjectFactory->gameObjectContainer->player->isClimbing = false;
	}
}


// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithJumping() {
	if (gameObjectFactory->gameObjectContainer->player->isFalling) {
		gameObjectFactory->gameObjectContainer->player->stopFalling();
		gameObjectFactory->gameObjectContainer->player->checkIfJumpPossible = false;
	}
	if (!gameObjectFactory->gameObjectContainer->player->isFalling && gameObjectFactory->gameObjectContainer->player->checkIfJumpPossible) {
		gameObjectFactory->gameObjectContainer->player->startJumping();
		gameObjectFactory->gameObjectContainer->player->checkIfJumpPossible = false;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform) {
	// check bottom left corner
	// check bottom right corner
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	for (int i = 0; i < gameObjectFactory->gameObjectContainer->platformHolder->numberOfElements; i++) {

		//bottom left corner 
		if (gameObjectFactory->collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, &gameObjectFactory->gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (gameObjectFactory->collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, &gameObjectFactory->gameObjectContainer->platformHolder->platforms[i])) { // isPointOnTopOfLine
			*flagPlatform = 1;
		}

		//bottom right corner 
		if (gameObjectFactory->collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition, &gameObjectFactory->gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (gameObjectFactory->collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, &gameObjectFactory->gameObjectContainer->platformHolder->platforms[i])) {// isPointOnTopOfLine
			*flagPlatform = 1;
		}
	}
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
	handleCollisionWithKong();
	handleCollisionWithPrincess();
	int flagLadder = 0;
	handleCollisionWithLadder(&flagLadder);
	int flagPlatform = 0;
	handleCollisionWithPlatform(gameObjectFactory->gameObjectContainer->player, &flagPlatform);

	if (!gameObjectFactory->gameObjectContainer->player->isClimbing) {
		if (flagPlatform) {
			screenManager->loadTexture(gameObjectFactory->gameObjectContainer->player, PLAYER_1_FILENAME);
			handleCollisionWithJumping();
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

		handleCollisionWithBarrel(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], quit, startAnotherRound);

		int flagPlatform = 0;
		handleCollisionWithPlatform(&gameObjectFactory->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], &flagPlatform);

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
