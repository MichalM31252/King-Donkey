#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

#include "./Game.h"
#include "./Constants.h"
#include "./game_screen/ScreenManager.h"
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "./game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h"
#include "./game_events/EventManager.h"
#include "./game_events/CollisionManager.h"
#include "./Platform.h"
#include "./PlatformHolder.h"
}

void Game::setUpFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void Game::setUpPlayer() { // (logic)
	Player* pla = new Player();
	pla->init("Mario_Run1.bmp");
	pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
	pla->setUpSrcRect();
	pla->setUpDestRect();
	player = pla;
}

void Game::setUpDonkeyKong() {
	GameObject* donkeyK = new GameObject();
	donkeyK->init("DonkeyKong.bmp");
	donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	donkeyK->setUpSrcRect();
	donkeyK->setUpDestRect();
	donkeyKong = donkeyK;
}

void Game::setUpPrincess() {
	GameObject* prin = new GameObject();
	prin->init("Princess.bmp");
	prin->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
	prin->setUpSrcRect();
	prin->setUpDestRect();
	princess = prin;
}

void Game::setUpPlatforms1() { // (logic)
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

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);
	platformHolder = platH;
}

void Game::setUpLadders1() { // (logic)
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
	ladderHolder = laddH;
}

void Game::setUpBarrels() {
	DynamicGameObject* barrel1 = new DynamicGameObject();
	barrel1->init("Barrel.bmp");
	barrel1->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel1->setUpSrcRect();
	barrel1->setUpDestRect();
	barrel1->objectSpeed = DEFAULT_BARREL_SPEED;

	BarrelHolder* barrelH = new BarrelHolder();
	initBarrelHolder(barrelH);
	addBarrel(barrelH, barrel1);

	barrelDispenser = new BarrelDispenser();
	barrelDispenser->barrelHolder = barrelH;
	barrelDispenser->setPosition(donkeyKong->xpos + donkeyKong->destRect.w +  + SMALL_MARGIN, donkeyKong->ypos);
}

void Game::setUpPlatforms2() { // (logic)
	Platform* plat1 = new Platform();
	plat1->setPosition(1, 400, SCREEN_WIDTH - 1, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(130, 130, 300, 300); // 4

	Platform* plat3 = new Platform();
	plat3->setPosition(1, 130, 130, 130); // 4

	Platform* plat4 = new Platform();
	plat4->setPosition(1, 130, 130, 130); // 4

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, SCREEN_WIDTH - 100 - LADDER_WIDTH, 80); // 4

	Platform* plat6 = new Platform();
	plat6->setPosition(SCREEN_WIDTH - 100 - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - 100, 230); // 4

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);
	addPlatform(platH, plat6);
	platformHolder = platH;
}

void Game::setUpLadders2() { // (logic)
	GameObject* ladd1 = new GameObject();
	ladd1->init("Ladder.bmp");
	ladd1->setPosition(SCREEN_WIDTH - 100 - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170); // yeah this actually sets the size
	ladd1->setDestRect(LADDER_WIDTH, 170);

	GameObject* ladd2 = new GameObject();
	ladd2->init("Ladder.bmp");
	ladd2->setPosition(SCREEN_WIDTH - 100 - LADDER_WIDTH - LADDER_WIDTH, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 150); // yeah this actually sets the size
	ladd2->setDestRect(LADDER_WIDTH, 150);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);
	ladderHolder = laddH;
}

void Game::setUpPlatforms3() { // (logic)
	Platform* plat1 = new Platform();
	plat1->setPosition(0, 400, SCREEN_WIDTH - 1, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(100, 300, SCREEN_WIDTH - 100, 300); // 2

	Platform* plat3 = new Platform();
	plat3->setPosition(100, 200, SCREEN_WIDTH - 100, 200); // 3

	Platform* plat4 = new Platform();
	plat4->setPosition(1, 130, SCREEN_WIDTH - 100, 130); // 4

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80); // 4

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);
	platformHolder = platH;
}

void Game::setUpLadders3() { // (logic)
	GameObject* ladd1 = new GameObject();
	ladd1->init("Ladder.bmp");
	ladd1->setPosition(SCREEN_WIDTH - 100 - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, 100); // yeah this actually sets the size
	ladd1->setDestRect(LADDER_WIDTH, 100);

	GameObject* ladd2 = new GameObject();
	ladd2->init("Ladder.bmp");
	ladd2->setPosition(100, 199);
	ladd2->setSrcRect(LADDER_WIDTH, 100); // yeah this actually sets the size
	ladd2->setDestRect(LADDER_WIDTH, 100);

	GameObject* ladd3 = new GameObject();
	ladd3->init("Ladder.bmp");
	ladd3->setPosition(SCREEN_WIDTH - 100 - LADDER_WIDTH, 129);
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
	ladderHolder = laddH;
}

void Game::setUpBoard(int boardId) { // (logic)
	setUpPlayer();
	setUpDonkeyKong();
	setUpPrincess();
	if (boardId == 1) {
		setUpPlatforms1();
		setUpLadders1();
	}
	if (boardId == 2) {
		setUpPlatforms2();
		setUpLadders2();
	}
	if (boardId == 3) {
		setUpPlatforms3();
		setUpLadders3();
	}
	setUpBarrels();
}

void Game::handleDifferentComputers() { // (logic) make every object dependent on deltaTime so it works the same on different computers
	tick2 = SDL_GetTicks();
	deltaTime = (tick2 - tick1) * 0.001;
	tick1 = tick2;
}

void Game::updateWorldTime() { // logic
	worldTime += deltaTime;
}

void Game::handleFPSTimer() { // logic
	fpsTimer += deltaTime;
	if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
		fps = frames * REFRESH_RATE;
		frames = 0;
		fpsTimer -= SECONDS_BETWEEN_REFRESH;
	};
}

// COLLISIONS

void Game::handleCollisionWithKong(CollisionManager *collisionManager, ScreenManager& screenManager) { // COLLISION WITH KONG
	if (collisionManager->checkCollisionBetweenRects(player->destRect, donkeyKong->destRect)) {
		closeGame(screenManager);
	}
}

void Game::handleCollisionWithPrincess(CollisionManager* collisionManager, ScreenManager& screenManager) { // COLLISION WITH PRINCESS
	if (collisionManager->checkCollisionBetweenRects(player->destRect, princess->destRect)) {
		closeGame(screenManager);
	}
}

void Game::handleCollisionWithLadder(CollisionManager* collisionManager, ScreenManager& screenManager, int *flagLadder) {
	for (int i = 0; i < ladderHolder->numberOfElements; i++) {
		if (collisionManager->checkIfInsideLadder(player->destRect, ladderHolder->ladders[i].destRect)) {
			*flagLadder = 1;
		}
	}

	if (*flagLadder) {
		player->isInsideLadder = true;
	}
	else {
		player->isInsideLadder = false;
		player->isClimbing = false;
	}
}

void Game::handleCollisionWithJumping() {
	if (player->isFalling) {
		player->stopFalling();
		player->checkIfJumpPossible = false;
	}
	if (!player->isFalling && player->checkIfJumpPossible) {
		player->startJumping();
		player->checkIfJumpPossible = false;
	}
}

void Game::handleFalling(DynamicGameObject *dynamicGameObject) {
	if (!dynamicGameObject->isJumping) {
		dynamicGameObject->startFalling();

		dynamicGameObject->accumulatedYMove += deltaTime * dynamicGameObject->gravity;
		int pixelsToMove = dynamicGameObject->accumulatedYMove / 1;
		if (pixelsToMove >= 1) {
			dynamicGameObject->ypos += 1;
			dynamicGameObject->accumulatedYMove -= 1;
		}
	}
}

void Game::handleJumping() {
	player->accumulatedYMove -= deltaTime * player->gravity;
	int pixelsToMove = player->accumulatedYMove / 1;
	if (pixelsToMove <= -1) {
		player->ypos -= 1;
		player->accumulatedYMove += 1;
	}
}

void Game::handleCollisionWithPlatform(CollisionManager* collisionManager, ScreenManager& screenManager, DynamicGameObject *gameObject , int* flagPlatform) {
	for (int i = 0; i < platformHolder->numberOfElements; i++) {
		if (collisionManager->checkObjectCollisionWithPlatform(gameObject->xpos, gameObject->ypos + gameObject->destRect.h, gameObject->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos) || collisionManager->checkObjectCollisionWithPlatform(gameObject->xpos + gameObject->destRect.w, gameObject->ypos + gameObject->destRect.h, gameObject->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos)) { // checking from left bottom corner || from the right corner
			if (!gameObject->isClimbing) { // we dont want collision with platform when climbing
				gameObject->ypos--; // Big problem // This throws the player on top of the platform
			}
		}
		if (collisionManager->checkObjectCollisionWithPlatform(gameObject->xpos, gameObject->ypos + gameObject->destRect.h + 1, gameObject->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos) || collisionManager->checkObjectCollisionWithPlatform(gameObject->xpos + gameObject->destRect.w, gameObject->ypos + gameObject->destRect.h + 1, gameObject->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos)) {
			*flagPlatform = 1;
		}
	}
}

void Game::drawElements(ScreenManager& screenManager) {
	donkeyKong->render(screenManager.screen);
	princess->render(screenManager.screen);

	for (int i = 0; i < platformHolder->numberOfElements; i++) {
		platformHolder->platforms[i].render(screenManager.screen);
	}

	for (int i = 0; i < ladderHolder->numberOfElements; i++) {
		ladderHolder->ladders[i].renderLadder(screenManager.screen);
	}

	for (int i = 0; i < barrelDispenser->barrelHolder->numberOfElements; i++) {
		barrelDispenser->barrelHolder->barrels[i].render(screenManager.screen);
	}

	player->render(screenManager.screen);
}

void Game::handleCurrentRound(ScreenManager& screenManager, EventManager& eventHandler, int *startAnotherRound) { // VisualManager is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) { // 1 frame of the game

		handleDifferentComputers();
		updateWorldTime();
		handleFPSTimer();

		screenManager.drawOutlineOfTheBoard(); // this first because it overwrites everything
		screenManager.drawAdditionalInfo(worldTime);

		CollisionManager collisionManager;

		// player collision
		handleCollisionWithKong(&collisionManager, screenManager);
		handleCollisionWithPrincess(&collisionManager, screenManager);
		int flagLadder = 0;
		handleCollisionWithLadder(&collisionManager, screenManager, &flagLadder);
		int flagPlatform = 0;
		handleCollisionWithPlatform(&collisionManager, screenManager, player ,&flagPlatform);

		if (!player->isClimbing) {
			if (flagPlatform) {
				handleCollisionWithJumping();
			}
			else {
				handleFalling(player);
			}
			if (player->isJumping) { // handle jumping
				handleJumping();
			}
		}

		if (player->isJumping && player->ypos <= player->jumpHeightStop) {
			player->stopJumping();
			player->startFalling();
		}

		// barrel collision
		

		barrelDispenser->updateBarrelDispenser(deltaTime);

		for (int i = 0; i < barrelDispenser->barrelHolder->numberOfElements; i++) {
			flagPlatform = 0;
			handleCollisionWithPlatform(&collisionManager, screenManager, &barrelDispenser->barrelHolder->barrels[i], &flagPlatform);
			if (flagPlatform) {
				if (barrelDispenser->barrelHolder->barrels[i].isFalling) {
					barrelDispenser->barrelHolder->barrels[i].stopFalling();
					barrelDispenser->barrelHolder->barrels[i].stopMove();
				}
				barrelDispenser->barrelHolder->barrels[i].moveStart(DEFAULT_BARREL_SPEED);
				barrelDispenser->barrelHolder->barrels[i].startMovingRight(deltaTime);
			}
			else {
				handleFalling(&barrelDispenser->barrelHolder->barrels[0]); // THE PROBLEM IS HERE
			}
			barrelDispenser->barrelHolder->barrels[i].update(deltaTime);
		}


		// Updating the game objects
		player->update(deltaTime);

		drawElements(screenManager);

		screenManager.serveNextFrame();

		eventHandler.handleEvents(&quit, deltaTime, player, startAnotherRound);

		frames++;
	};
}

void Game::handleRound(ScreenManager& screenManager, int startAnotherRound) { // yeah make this a different class in the future	
	EventManager eventHandler;
	
	setUpFramerate();

	if (startAnotherRound) {
		if (startAnotherRound == 1) {
			setUpBoard(1);
		}
		if (startAnotherRound == 2) {
			setUpBoard(2);
		}
		if (startAnotherRound == 3) {
			setUpBoard(3);
		}
	}
	else {
		setUpBoard(1);
	}

	handleCurrentRound(screenManager, eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(screenManager, startAnotherRound);
	}
}

void Game::initGame() {
	ScreenManager screenManager;
	screenManager.setUpSDL(); // this should be set once

	int startAnotherRound = 0;
	handleRound(screenManager, startAnotherRound);

	closeGame(screenManager);
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(ScreenManager& screenManager) { // change this into a vector to be more efficient (so it can destroy every gameobject)
	SDL_FreeSurface(screenManager.charset);
	SDL_FreeSurface(screenManager.screen);
	SDL_DestroyTexture(screenManager.scrtex);
	SDL_DestroyWindow(screenManager.window);
	SDL_DestroyRenderer(screenManager.renderer);
	SDL_Quit();
	exit(0);
}
