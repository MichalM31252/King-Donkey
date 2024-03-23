#define _USE_MATH_DEFINES

extern "C" {
#include "./Game.h"
}

// MOVE TO SCREEN MANAGER ? 
void Game::createFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void Game::createPlayer() { // (logic)
	Player* pla = new Player();
	pla->init(PLAYER_1_FILENAME);
	pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
	pla->createSrcRect();
	pla->createDestRect();
	pla->isPlayer = true;

	gameObjectContainer->player = pla; //
}

void Game::createDonkeyKong() {
	GameObject* donkeyK = new GameObject();
	donkeyK->init("DonkeyKong.bmp");
	donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	donkeyK->createSrcRect();
	donkeyK->createDestRect();

	gameObjectContainer->donkeyKong = donkeyK; // 
}

void Game::createPrincess() {
	GameObject* prin = new GameObject();
	prin->init("Princess.bmp");
	prin->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
	prin->createSrcRect();
	prin->createDestRect();

	gameObjectContainer->princess = prin;//
}

void Game::createPlatforms1() { // (logic)
	Platform* plat1 = new Platform();
	plat1->setPosition(1, 400, 400, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(400, 400, 500, 300); // 2

	Platform* plat3 = new Platform();
	plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300); // 3

	Platform* plat4 = new Platform();
	plat4->setPosition(1, 130, 570, 130); // 4

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80); // 4

	PlatformHolder* pH = new PlatformHolder();
	initPlatformHolder(pH);
	addPlatform(pH, plat1);
	addPlatform(pH, plat2);
	addPlatform(pH, plat3);
	addPlatform(pH, plat4);
	addPlatform(pH, plat5);

	gameObjectContainer->platformHolder = pH; //
}

void Game::createLadders1() { // (logic)
	GameObject* ladd1 = new GameObject();
	ladd1->init("Ladder.bmp");
	ladd1->setPosition(525, 129);
	ladd1->setSrcRect(LADDER_WIDTH, 170); // yeah this actually sets the size
	ladd1->setDestRect(LADDER_WIDTH, 170);

	GameObject* ladd2 = new GameObject();
	ladd2->init("Ladder.bmp");
	ladd2->setPosition(250, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 50); // yeah this actually sets the size
	ladd2->setDestRect(LADDER_WIDTH, 50);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);
	gameObjectContainer->ladderHolder = laddH;
}

void Game::createBarrels() {
	DynamicGameObject* barrel1 = new DynamicGameObject();
	barrel1->init(BARREL_1_FILENAME);
	barrel1->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel1->createSrcRect();
	barrel1->createDestRect();
	barrel1->objectSpeed = DEFAULT_BARREL_SPEED;

	BarrelHolder* barrelH = new BarrelHolder();
	initBarrelHolder(barrelH);
	addBarrel(barrelH, barrel1);

	gameObjectContainer->barrelDispenser = new BarrelDispenser();
	gameObjectContainer->barrelDispenser->barrelHolder = barrelH;
	gameObjectContainer->barrelDispenser->setPosition(gameObjectContainer->donkeyKong->xpos + gameObjectContainer->donkeyKong->destRect.w +  + SMALL_MARGIN, gameObjectContainer->donkeyKong->ypos);
}

void Game::createPlatforms2() { // (logic)
	Platform* plat1 = new Platform();
	plat1->setPosition(TINY_MARGIN, 400, SCREEN_WIDTH - 1, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(130, 130, 300, 300); // 4

	Platform* plat3 = new Platform();
	plat3->setPosition(TINY_MARGIN, 130, 130, 130); // 4

	Platform* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, 130, 130); // 4

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 80); // 4

	Platform* plat6 = new Platform();
	plat6->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - LARGE_MARGIN, 230); // 4

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);
	addPlatform(platH, plat6);

	gameObjectContainer->platformHolder = platH; //
}

void Game::createLadders2() { // (logic)
	GameObject* ladd1 = new GameObject();
	ladd1->init("Ladder.bmp");
	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170); // yeah this actually sets the size
	ladd1->setDestRect(LADDER_WIDTH, 170);

	GameObject* ladd2 = new GameObject();
	ladd2->init("Ladder.bmp");
	ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 150); // yeah this actually sets the size
	ladd2->setDestRect(LADDER_WIDTH, 150);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);

	gameObjectContainer->ladderHolder = laddH;
}

void Game::createPlatforms3() { // (logic)
	Platform* plat1 = new Platform();
	plat1->setPosition(STARTING_X, 400, SCREEN_WIDTH - TINY_MARGIN, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(LARGE_MARGIN, 300, SCREEN_WIDTH - LARGE_MARGIN, 300); // 2

	Platform* plat3 = new Platform();
	plat3->setPosition(LARGE_MARGIN, 200, SCREEN_WIDTH - LARGE_MARGIN, 200); // 3

	Platform* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, SCREEN_WIDTH - LARGE_MARGIN, 130); // 4

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80); // 4

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);

	gameObjectContainer->platformHolder = platH; //
}

void Game::createLadders3() { // (logic)
	GameObject* ladd1 = new GameObject();
	ladd1->init("Ladder.bmp");
	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN); // yeah this actually sets the size
	ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	GameObject* ladd2 = new GameObject();
	ladd2->init("Ladder.bmp");
	ladd2->setPosition(LARGE_MARGIN, 199);
	ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN); // yeah this actually sets the size
	ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	GameObject* ladd3 = new GameObject();
	ladd3->init("Ladder.bmp");
	ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
	ladd3->setSrcRect(LADDER_WIDTH, 70); // yeah this actually sets the size
	ladd3->setDestRect(LADDER_WIDTH, 70);

	GameObject* ladd4 = new GameObject();
	ladd4->init("Ladder.bmp");
	ladd4->setPosition(250, 79);
	ladd4->setSrcRect(LADDER_WIDTH, 50); // yeah this actually sets the size
	ladd4->setDestRect(LADDER_WIDTH, 50);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);
	addLadder(laddH, ladd3);
	addLadder(laddH, ladd4);
	gameObjectContainer->ladderHolder = laddH;
}

void Game::createBoard(int boardId) { // (logic)
	createPlayer();
	createDonkeyKong();
	createPrincess();
	if (boardId == 1) {
		createPlatforms1();
		createLadders1();
	}
	if (boardId == 2) {
		createPlatforms2();
		createLadders2();
	}
	if (boardId == 3) {
		createPlatforms3();
		createLadders3();
	}
	createBarrels();
}

void Game::handleDifferentComputers() { // (logic) make every object dependent on deltaTime so it works the same on different computers
	tick2 = SDL_GetTicks();
	deltaTime = (tick2 - tick1) * 0.001;
	tick1 = tick2;
}

void Game::updateWorldTime() { 
	worldTime += deltaTime;
}

void Game::handleFPSTimer() { 
	fpsTimer += deltaTime;
	if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
		fps = frames * REFRESH_RATE;
		frames = 0;
		fpsTimer -= SECONDS_BETWEEN_REFRESH;
	};
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithKong(CollisionManager *collisionManager) { // COLLISION WITH KONG
	if (collisionManager->isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPrincess(CollisionManager* collisionManager) { // COLLISION WITH PRINCESS
	if (collisionManager->isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
		closeGame();
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithBarrel(CollisionManager* collisionManager, DynamicGameObject* barrel, bool *quit, int *startAnotherRound) {
	if (collisionManager->isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*quit = true;
		*startAnotherRound = 1;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithLadder(CollisionManager* collisionManager, int *flagLadder) {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		if (collisionManager->isRectInsideLadder(gameObjectContainer->player->destRect, gameObjectContainer->ladderHolder->ladders[i].destRect)) {
			*flagLadder = 1;
		}
	}
	if (*flagLadder) {
		gameObjectContainer->player->isInsideLadder = true;
	}
	else {
		gameObjectContainer->player->isInsideLadder = false;
		gameObjectContainer->player->isClimbing = false;
	}
}


// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithJumping() {
	if (gameObjectContainer->player->isFalling) {
		gameObjectContainer->player->stopFalling();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
	if (!gameObjectContainer->player->isFalling && gameObjectContainer->player->checkIfJumpPossible) {
		gameObjectContainer->player->startJumping();
		gameObjectContainer->player->checkIfJumpPossible = false;
	}
}

// MOVE TO COLLISION MANAGER
void Game::handleCollisionWithPlatform(CollisionManager* collisionManager, DynamicGameObject *gameObject , int* flagPlatform) {
	// check bottom left corner
	// check bottom right corner
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	for (int i = 0; i < gameObjectContainer->platformHolder->numberOfElements; i++) {

		//bottom left corner 
		if (collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, &gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (collisionManager->isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, &gameObjectContainer->platformHolder->platforms[i])) { // isPointOnTopOfLine
			*flagPlatform = 1;
		}

		//bottom right corner 
		if (collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition, &gameObjectContainer->platformHolder->platforms[i])) { // isPointInsideLine
			if (!gameObject->isClimbing) {
				gameObject->ypos--;
				yPosition--;
			}
		}
		if (collisionManager->isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, &gameObjectContainer->platformHolder->platforms[i])) {// isPointOnTopOfLine
			*flagPlatform = 1;
		}
	}
	// after that you need to add collision for the top left and top right corner
	// but in their case you need to stop the player from moving up
}

// MOVE TO TEXTURE MANAGER
void Game::drawPlatforms() {
	for (int i = 0; i < gameObjectContainer->platformHolder->numberOfElements; i++) {
		gameObjectContainer->platformHolder->platforms[i].render(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawLadders() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		gameObjectContainer->ladderHolder->ladders[i].renderLadder(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawBarrels() {
	for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {
		gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].render(screenManager->screen);
	}
}

// MOVE TO TEXTURE MANAGER
void Game::drawElements() {
	gameObjectContainer->donkeyKong->render(screenManager->screen);
	gameObjectContainer->princess->render(screenManager->screen);
	gameObjectContainer->player->render(screenManager->screen);

	drawPlatforms();
	drawLadders();
	drawBarrels();
}


// MOVE TO GAME OBJECT MANAGER
void Game::handlePlayer(CollisionManager* collisionManager) { // player collision
	handleCollisionWithKong(collisionManager);
	handleCollisionWithPrincess(collisionManager);
	int flagLadder = 0;
	handleCollisionWithLadder(collisionManager, &flagLadder);
	int flagPlatform = 0;
	handleCollisionWithPlatform(collisionManager, gameObjectContainer->player, &flagPlatform);

	if (!gameObjectContainer->player->isClimbing) {
		if (flagPlatform) {
			gameObjectContainer->player->textureManager.loadTexture(PLAYER_1_FILENAME);
			handleCollisionWithJumping();
		}
		else {
			PhysicsManager::handleFalling(gameObjectContainer->player, deltaTime);
		}
		if (gameObjectContainer->player->isJumping) { // handle jumping
			gameObjectContainer->player->jump(deltaTime);
		}
	}

	if (gameObjectContainer->player->isJumping && gameObjectContainer->player->ypos <= gameObjectContainer->player->jumpHeightStop) {
		gameObjectContainer->player->stopJumping();
		gameObjectContainer->player->startFalling();
	}
}

// MOVE TO GAME OBJECT MANAGER
void Game::handleBarrels(CollisionManager* collisionManager, bool *quit, int* startAnotherRound) {
	gameObjectContainer->barrelDispenser->updateBarrelDispenser(deltaTime);

	for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {

		handleCollisionWithBarrel(collisionManager, &gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], quit, startAnotherRound);

		int flagPlatform = 0;
		handleCollisionWithPlatform(collisionManager, &gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], &flagPlatform);

		if (flagPlatform) {
			if (gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].isFalling) {
				gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopFalling();
				gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].stopMove();
			}
			gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].moveStart(DEFAULT_BARREL_SPEED);
			gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].startMovingRight(deltaTime);
		}
		else {
			PhysicsManager::handleFalling(&gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], deltaTime); // THE PROBLEM IS HERE
		}
		gameObjectContainer->barrelDispenser->barrelHolder->barrels[i].update(deltaTime);
	}
}

// MOVE TO ROUND MANAGER
void Game::handleCurrentRound(KeyboardManager& eventHandler, int *startAnotherRound) { // VisualManager is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) {

		handleDifferentComputers();
		updateWorldTime();
		handleFPSTimer();

		screenManager->drawOutlineOfTheBoard(); // this first because it overwrites everything
		screenManager->drawAdditionalInfo(worldTime);

		// This should be a part of GameObjectManager
		CollisionManager collisionManager;
		handlePlayer(&collisionManager); // player collision
		handleBarrels(&collisionManager, &quit, startAnotherRound); // barrel collision

		gameObjectContainer->player->update(deltaTime);
		// 

		drawElements();

		screenManager->serveNextFrame();

		eventHandler.handleEvents(&quit, deltaTime, gameObjectContainer->player, startAnotherRound);

		frames++;
	};
}

// MOVE TO ROUND MANAGER
void Game::handleRound(int startAnotherRound) { // yeah make this a different class in the future	
	KeyboardManager eventHandler;
	createFramerate();
	if (startAnotherRound) {
		if (startAnotherRound == BOARD_ID_A) {
			createBoard(BOARD_ID_A);
		}
		if (startAnotherRound == BOARD_ID_B) {
			createBoard(BOARD_ID_B);
		}
		if (startAnotherRound == BOARD_ID_C) {
			createBoard(BOARD_ID_C);
		}
	}
	else {
		createBoard(BOARD_ID_A);
	}

	handleCurrentRound(eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(startAnotherRound);
	}
}

void Game::initGame() {
	ScreenManager *screenMan = new ScreenManager();

	screenManager = screenMan;

	GameObjectContainer* ga = new GameObjectContainer();
	gameObjectContainer = ga;

	screenManager->createSDL(); // this should be set once

	int startAnotherRound = 0;
	handleRound(startAnotherRound);

	closeGame();
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
