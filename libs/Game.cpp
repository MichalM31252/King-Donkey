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
	plat1->setPosition(SCREEN_WIDTH - 300, 400, SCREEN_WIDTH - 10, 400);
	platform1 = plat1;

	Platform* plat2 = new Platform();
	plat2->setPosition(300, 300, 400, 400);
	platform2 = plat2;

	PlatformHolder* platH = new PlatformHolder();
	init(platH);
	addPlatform(platH, platform1);
	addPlatform(platH, platform2);
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

void Game::handleGame(VisualManager& visualManager, EventManager& eventHandler) { // VisualManager is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) { // 1 frame of the game

		handleDifferentComputers();
		updateWorldTime();
		handleFPSTimer();

		visualManager.drawOutlineOfTheBoard(); // this first because it overwrites everything
		visualManager.drawAdditionalInfo(worldTime);

		// Updating the game objects
		player->update(deltaTime);
		// donkeyKong->update(deltaTime);

		// Checking for collision
		Collider collider;
		collider.checkCollision(player->destRect, donkeyKong->destRect);
		if (collider.isColliding) {
			printf("COLLIDING\n");
			closeGame(visualManager);
		}

		// left bottom corner checking

		

		// showing everything on the screen 
		player->render(visualManager.screen);
		donkeyKong->render(visualManager.screen);
		//platform1->render(visualManager.screen);
		/*platform2->render(visualManager.screen);*/

		for (int i = 0; i < platformHolder->numberOfElements; i++) {
			collider.checkPlayerCollisionWithPlatform(player->xpos, player->ypos, player->destRect.h, platformHolder->platforms[i].x1pos, platformHolder->platforms[i].y1pos, platformHolder->platforms[i].x2pos, platformHolder->platforms[i].y2pos);
			platformHolder->platforms[i].render(visualManager.screen);
		}

		// visualManager.drawGameObjects(); or something like that ??

		//GameObject player(STARTING_X_PLAYER, STARTING_Y_PLAYER, 1);
		//player.init("Mario_Run1.bmp");
		//player.render(visualManager.screen);
		

		// distance += etiSpeed * deltaTime; // make gam  eObjects dependent on deltaTime so it works the same on different computers          
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	 
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, 64, 64); // an image on the specified position	 



		visualManager.serveNextFrame();

		eventHandler.handleEvents(&quit, deltaTime, player);

		frames++;
	};
}

void Game::setUpGame(VisualManager& visualManager) {
	visualManager.setUpVisuals();
	setUpFramerate();
	setUpGameObjects(visualManager.screen); // here
}

void Game::initGame() {
	VisualManager visualManager;
	EventManager eventHandler;

	setUpGame(visualManager);
	handleGame(visualManager, eventHandler);
	closeGame(visualManager);
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(VisualManager& visualManager) { // change this into a vector to be more efficient (so it can destroy every gameobject)
	SDL_FreeSurface(visualManager.charset);
	SDL_FreeSurface(visualManager.screen);
	SDL_DestroyTexture(visualManager.scrtex);
	SDL_DestroyWindow(visualManager.window);
	SDL_DestroyRenderer(visualManager.renderer);
	SDL_Quit();
	exit(0);
}
