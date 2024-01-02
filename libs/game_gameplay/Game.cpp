#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "Game.h"
	#include "../Constants.h"
	#include "../game_visual/VisualHandler.h"
	#include "./EventHandler.h"
}







void Game::setUpFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void Game::setUpGameObjects() { // (logic)
	distance = 0; // the distance of the eti sign (this could maybe work for collision detection)
	etiSpeed = 1; // speed of the eti sign
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



void Game::handleGame(VisualHandler& visualHandler, EventHandler& eventHandler) { // visualHandler is passed by reference, can't be an const because it's methods change the object
	bool quit = false;
	while (!quit) { // 1 frame of the game

		this->handleDifferentComputers();
		this->updateWorldTime();
		this->handleFPSTimer();

		// distance += etiSpeed * deltaTime; // make gameObjects dependent on deltaTime so it works the same on different computers          
		// visualHandler.DrawSurface(screen, eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	   
		
		visualHandler.drawOutlineOfTheBoard();
		visualHandler.drawAdditionalInfo(worldTime);
		visualHandler.serveNextFrame();

		eventHandler.handleEvents(&quit);

		frames++;
	};
}

void Game::setUpGame(VisualHandler& visualHandler) {
	visualHandler.setUpVisuals();
	this->setUpFramerate();
	this->setUpGameObjects();
}

void Game::initGame() {
	VisualHandler visualHandler;
	EventHandler eventHandler;

	this->setUpGame(visualHandler);
	this->handleGame(visualHandler, eventHandler);
	this->closeGame(visualHandler);
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(VisualHandler& visualHandler) { // change this into a vector to be more efficient (so it can destroy every gameobject)
	SDL_FreeSurface(visualHandler.charset);
	SDL_FreeSurface(visualHandler.screen);
	SDL_DestroyTexture(visualHandler.scrtex);
	SDL_DestroyWindow(visualHandler.window);
	SDL_DestroyRenderer(visualHandler.renderer);
	SDL_Quit();
	exit(0);
}
