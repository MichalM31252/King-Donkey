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

void Game::setUpGameObjects(SDL_Surface* screen) { // (logic)
	Player *pla = new Player();
	pla->init("Mario_Run1.bmp");
	pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER - 100);
	pla->setUpSrcRect();
	pla->setUpDestRect();
	player = pla;

	GameObject *donkeyK = new GameObject();
	donkeyK->init("DonkeyKong.bmp");
	donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	donkeyK->setUpSrcRect();
	donkeyK->setUpDestRect();
	donkeyKong = donkeyK;

	Platform *plat1 = new Platform();
	plat1->setPosition(1, 400, 400, 400); // 1

	Platform* plat2 = new Platform();
	plat2->setPosition(400, 400, 500, 300); // 2

	Platform* plat3 = new Platform();
	plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300); // 3

	//Platform* plat4 = new Platform();
	//plat4->setPosition(1, 130, SCREEN_WIDTH - 1, 130); // 4

	//Platform *plat1 = new Platform();
	//plat1->setPosition(400, 400, SCREEN_WIDTH - 10, 400);

	//Platform* plat2 = new Platform();
	//plat2->setPosition(300, 300, 400, 400);

	//Platform* plat3 = new Platform();
	//plat3->setPosition(200, 300, 100, 300);

	PlatformHolder* platH = new PlatformHolder();
	init(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	//addPlatform(platH, plat4);

	platformHolder = platH;
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

void Game::handleCurrentRound(ScreenManager& screenManager, EventManager& eventHandler, int *startAnotherRound) { // VisualManager is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) { // 1 frame of the game

		handleDifferentComputers();
		updateWorldTime();
		handleFPSTimer();

		screenManager.drawOutlineOfTheBoard(); // this first because it overwrites everything
		screenManager.drawAdditionalInfo(worldTime);

		CollisionManager collisionManager;

		collisionManager.checkCollisionBetweenRects(player->destRect, donkeyKong->destRect);
		if (collisionManager.isColliding) {
			closeGame(screenManager);
		}

		int flag = 0;
		for (int i = 0; i < platformHolder->numberOfElements; i++) {
			// this should be check one pixel below current position because from the logics perspective the player is inside the platform
			// maybe check current pixel and one below it to check if platform is rising
			
			// player collision with platform
			if (collisionManager.checkObjectCollisionWithPlatform(player->xpos, player->ypos + player->destRect.h, player->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos) || collisionManager.checkObjectCollisionWithPlatform(player->xpos + player->destRect.w, player->ypos + player->destRect.h, player->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos)) { // checking from left bottom corner || from the right corner
				printf("COLLIDING WITH PLATFORM\n");
				player->ypos--;
			}
			if (collisionManager.checkObjectCollisionWithPlatform(player->xpos, player->ypos + player->destRect.h + 1, player->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos) || collisionManager.checkObjectCollisionWithPlatform(player->xpos + player->destRect.w, player->ypos + player->destRect.h + 1, player->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos)) {
				printf("COLLIDING WITH PLATFORM FROM BELOW\n");
				flag = 1;
			}
			platformHolder->platforms[i].render(screenManager.screen);
		}

		if (flag) {
			player->stopFalling();
			// player->ypos--;
		}
		else {
			player->startFalling();

			player->accumulatedYMove += deltaTime * player->gravity;
			int pixelsToMove = player->accumulatedYMove / 1;
			if (pixelsToMove >= 1) {
				player->ypos += 1;
				player->accumulatedYMove -= 1;
			}
			
		}



		//if (player->isFalling && player->xpos > 200) {
		//	int ok = 1;
		//}

		// Updating the game objects
		player->update(deltaTime);
		// donkeyKong->update(deltaTime);

		// Checking for collision


		// left bottom corner checking

		

		// showing everything on the screen 
		player->render(screenManager.screen);
		donkeyKong->render(screenManager.screen);

		// screenManager->drawElements


		

		// distance += etiSpeed * deltaTime; // make gam  eObjects dependent on deltaTime so it works the same on different computers          
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	 
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, 64, 64); // an image on the specified position	 



		screenManager.serveNextFrame();

		eventHandler.handleEvents(&quit, deltaTime, player, startAnotherRound);

		frames++;
	};
}

void Game::setUpRound(ScreenManager& screenManager) { // (logic)
	setUpFramerate();
	setUpGameObjects(screenManager.screen);
}

void Game::handleRound(ScreenManager& screenManager) { // yeah make this a different class in the future	
	EventManager eventHandler;
	
	setUpRound(screenManager);
	int startAnotherRound = 0;
	handleCurrentRound(screenManager, eventHandler, &startAnotherRound);

	if (startAnotherRound) {
		handleRound(screenManager);
	}
	// if this returns n then recurence -> handleRound(screenManager, eventHandler);
}

void Game::initGame() {
	ScreenManager screenManager;

	screenManager.setUpSDL(); // only this should be set once
	handleRound(screenManager);

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
