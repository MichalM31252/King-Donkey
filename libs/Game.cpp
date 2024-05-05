#define _USE_MATH_DEFINES

extern "C" {
#include "./Game.h"
}

Game::Game() {
	ScreenManager* screenMan = new ScreenManager();
	screenManager = screenMan;

	GameObjectManager* gameObjectMan = new GameObjectManager();
	gameObjectManager = gameObjectMan;
}


// MOVE TO ROUND MANAGER
void Game::handleCurrentRound(KeyboardManager& eventHandler, int *startAnotherRound) { // VisualManager is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) {

		screenManager->handleDifferentComputers();
		screenManager->updateWorldTime();
		screenManager->handleFPSTimer();

		screenManager->drawOutlineOfTheBoard();
		screenManager->drawAdditionalInfo(screenManager->worldTime);

		handlePlayer(); // player collision
		handleBarrels(&quit, startAnotherRound); // barrel collision

		gameObjectManager->gameObjectContainer->player->update(screenManager->deltaTime);

		drawElements();

		screenManager->serveNextFrame();

		eventHandler.handleEvents(&quit, screenManager->deltaTime, gameObjectManager->gameObjectContainer->player, startAnotherRound);

		screenManager->frames++;
	};
}

// MOVE TO ROUND MANAGER
void Game::handleRound(int startAnotherRound) { // yeah make this a different class in the future	
	KeyboardManager eventHandler;
	screenManager->createFramerate();
	if (startAnotherRound) {
		if (startAnotherRound == BOARD_ID_A) {
			gameObjectManager->createBoard(BOARD_ID_A);
		}
		if (startAnotherRound == BOARD_ID_B) {
			gameObjectManager->createBoard(BOARD_ID_B);
		}
		if (startAnotherRound == BOARD_ID_C) {
			gameObjectManager->createBoard(BOARD_ID_C);
		}
	}
	else {
		gameObjectManager->createBoard(BOARD_ID_A);
	}

	handleCurrentRound(eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(startAnotherRound);
	}
}

void Game::initGame() {
	screenManager->createSDL(); // this should be set once

	int startAnotherRound = 0;
	handleRound(startAnotherRound);

	closeGame();
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithKong() {
	if (gameObjectManager->collisionManager->isCollisionBetweenRects(gameObjectManager->gameObjectContainer->player->destRect, gameObjectManager->gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPrincess() {
	if (gameObjectManager->collisionManager->isCollisionBetweenRects(gameObjectManager->gameObjectContainer->player->destRect, gameObjectManager->gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound) {
	if (gameObjectManager->collisionManager->isCollisionBetweenRects(gameObjectManager->gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithLadder(int* flagLadder) {
	for (int i = 0; i < gameObjectManager->gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (gameObjectManager->collisionManager->isRectInsideLadder(gameObjectManager->gameObjectContainer->player->destRect, gameObjectManager->gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			*flagLadder = 1;
		}
	}
	if (*flagLadder) {
		gameObjectManager->gameObjectContainer->player->isInsideLadder = true;
	}
	else {
		gameObjectManager->gameObjectContainer->player->isInsideLadder = false;
		gameObjectManager->gameObjectContainer->player->isClimbing = false;
	}
}


// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithJumping() {
	if (gameObjectManager->gameObjectContainer->player->isFalling) {
		gameObjectManager->gameObjectContainer->player->stopFalling();
		gameObjectManager->gameObjectContainer->player->checkIfJumpPossible = false;
	}
	if (!gameObjectManager->gameObjectContainer->player->isFalling && gameObjectManager->gameObjectContainer->player->checkIfJumpPossible) {
		gameObjectManager->gameObjectContainer->player->startJumping();
		gameObjectManager->gameObjectContainer->player->checkIfJumpPossible = false;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform) {
	// check bottom left corner
	// check bottom right corner
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	for (int i = 0; i < gameObjectManager->gameObjectContainer->platformHolder->numberOfElements; i++) {

		//bottom left corner 
		if (gameObjectManager->collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, &gameObjectManager->gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (gameObjectManager->collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, &gameObjectManager->gameObjectContainer->platformHolder->platforms[i])) { // isPointOnTopOfLine
			*flagPlatform = 1;
		}

		//bottom right corner 
		if (gameObjectManager->collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition, &gameObjectManager->gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (gameObjectManager->collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, &gameObjectManager->gameObjectContainer->platformHolder->platforms[i])) {// isPointOnTopOfLine
			*flagPlatform = 1;
		}
	}
	// after that you need to add collision for the top left and top right corner
	// but in their case you need to stop the player from moving up
}

// MOVE TO TEXTURE MANAGER
void Game::drawPlatforms() {
	for (int i = 0; i < gameObjectManager->gameObjectContainer->platformHolder->numberOfElements; i++) {
		gameObjectManager->gameObjectContainer->platformHolder->platforms[i].render(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawLadders() {
	for (int i = 0; i < gameObjectManager->gameObjectContainer->ladderHolder->numberOfElements; i++) {
		gameObjectManager->gameObjectContainer->ladderHolder->ladders[i].renderLadder(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawBarrels() {
	for (int i = 0; i < gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {
		gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].render(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawElements() { // don't repeat yourself
	gameObjectManager->gameObjectContainer->donkeyKong->render(screenManager->screen);
	gameObjectManager->gameObjectContainer->princess->render(screenManager->screen);
	gameObjectManager->gameObjectContainer->player->render(screenManager->screen);

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
	handleCollisionWithPlatform(gameObjectManager->gameObjectContainer->player, &flagPlatform);

	if (!gameObjectManager->gameObjectContainer->player->isClimbing) {
		if (flagPlatform) {
			gameObjectManager->gameObjectContainer->player->textureManager.loadTexture(PLAYER_1_FILENAME);
			handleCollisionWithJumping();
		}
		else {
			PhysicsManager::handleFalling(gameObjectManager->gameObjectContainer->player, screenManager->deltaTime);
		}
		if (gameObjectManager->gameObjectContainer->player->isJumping) { // handle jumping
			gameObjectManager->gameObjectContainer->player->jump(screenManager->deltaTime);
		}
	}

	if (gameObjectManager->gameObjectContainer->player->isJumping && gameObjectManager->gameObjectContainer->player->ypos <= gameObjectManager->gameObjectContainer->player->jumpHeightStop) {
		gameObjectManager->gameObjectContainer->player->stopJumping();
		gameObjectManager->gameObjectContainer->player->startFalling();
	}
}

// MOVE TO GAME OBJECT MANAGER
void Game::handleBarrels(bool* quit, int* startAnotherRound) {
	gameObjectManager->gameObjectContainer->barrelDispenser->updateBarrelDispenser(screenManager->deltaTime);

	for (int i = 0; i < gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {

		handleCollisionWithBarrel(&gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], quit, startAnotherRound);

		int flagPlatform = 0;
		handleCollisionWithPlatform(&gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], &flagPlatform);

		if (flagPlatform) {
			if (gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].isFalling) {
				gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopFalling();
				gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopMove();
			}
			gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].moveStart(DEFAULT_BARREL_SPEED);
			gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].startMovingRight(screenManager->deltaTime);
		}
		else {
			PhysicsManager::handleFalling(&gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], screenManager->deltaTime); // THE PROBLEM IS HERE
		}
		gameObjectManager->gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].update(screenManager->deltaTime);
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
