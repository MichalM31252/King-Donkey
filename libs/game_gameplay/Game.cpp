#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"

#include "Game.h"
#include "../Constants.h"
#include "../game_visual/VisualManager.h"
#include "../game_gameplay/GameObject.h"
#include "./EventManager.h"
}

void Game::setUpFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void Game::setUpGameObjects(SDL_Surface* screen) { // (logic)
	GameObject *pla = new GameObject(STARTING_X_PLAYER, STARTING_Y_PLAYER, 1);
	pla->init("Mario_Run1.bmp");
	player = pla;

	// GameObject kingDonkey(0, 0, 0); // this can be here
	// GameObject princess(0, 0, 0); // this can be here
	// GameObject barrel(0, 0, 0); 
	// GameObject ladder(0, 0, 0);
	// GameObject platform(0, 0, 0);
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

		// visualManager.drawGameObjects(); or something like that ??

		//GameObject player(STARTING_X_PLAYER, STARTING_Y_PLAYER, 1);
		//player.init("Mario_Run1.bmp");
		//player.render(visualManager.screen);
		player->render(visualManager.screen);

		// distance += etiSpeed * deltaTime; // make gam  eObjects dependent on deltaTime so it works the same on different computers          
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	 
		// visualManager.DrawSurface(visualManager.screen, visualManager.eti, 64, 64); // an image on the specified position	 

		visualManager.serveNextFrame();

		eventHandler.handleEvents(& quit, deltaTime, player);

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
