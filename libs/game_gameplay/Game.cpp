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

void Game::SDLCheck() { // checks if SDL was initialized correctly
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
		printf("SDL_Init error: %s\n", SDL_GetError());
		this->closeGame();
	}
}

void Game::SDLCreateWindowAndRenderer() {
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		this->closeGame();
	};
}

void Game::SDLSetHint() {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void Game::SDLSetRenderLogicalSize() {
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::SDLSetDefaultDrawColor() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Game::SDLSetWindowTitle() {
	SDL_SetWindowTitle(window, "192928 Michal Malinowski");
}

void Game::SDLSetCharset() {
	charset = SDL_LoadBMP("./cs8x8.bmp"); 
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		this->closeGame(charset, screen, scrtex, window, renderer);
	};
}

void Game::SDLSetScreen() {
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void Game::SDLSetTexture() {
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::SDLSetEtiLogo() {
	eti = SDL_LoadBMP("./eti.bmp"); 
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		this->closeGame(charset, screen, scrtex, window, renderer);
	};
}

void Game::SDLHideCursor() {
	SDL_ShowCursor(SDL_DISABLE); // hides the cursor
}

void Game::SDLSetColorKey() {
	SDL_SetColorKey(charset, true, 0x000000); 
}


void Game::setUpFramerate() {
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void Game::setUpGameObjects() {
	distance = 0; // the distance of the eti sign (this could maybe work for collision detection)
	etiSpeed = 1; // speed of the eti sign
}

void Game::handleDifferentComputers() { // make every object dependent on deltaTime so it works the same on different computers
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

void Game::serveNextFrame() {
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Game::handleGame(VisualHandler& visualHandler, EventHandler& eventHandler) { // visualHandler is passed by reference, can't be an const because it's methods change the object
	visualHandler.setColors(screen);
	bool quit = false;
	
	while (!quit) { // 1 frame of the game

		this->handleDifferentComputers();
		this->updateWorldTime();
		this->handleFPSTimer();

		// distance += etiSpeed * deltaTime; // make gameObjects dependent on deltaTime so it works the same on different computers          
		// visualHandler.DrawSurface(screen, eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	   
		
		visualHandler.drawOutlineOfTheBoard(screen);
		visualHandler.drawAdditionalInfo(screen, worldTime, charset);

		this->serveNextFrame(); // refactor so visualHabndler serves the next frame

		eventHandler.handleEvents(&quit);

		frames++;
	};
}

void Game::initGame() {

	VisualHandler visualHandler;
	EventHandler eventHandler;

	this->SDLCheck();
	this->SDLCreateWindowAndRenderer();
	this->SDLSetHint();
	this->SDLSetRenderLogicalSize();
	this->SDLSetDefaultDrawColor();
	this->SDLSetWindowTitle();
	this->SDLSetCharset();
	this->SDLSetScreen();
	this->SDLSetTexture();
	this->SDLSetEtiLogo();
	this->SDLHideCursor();
	this->SDLSetColorKey();

	
	
	
	this->setUpFramerate();
	this->setUpGameObjects();

	this->handleGame(visualHandler, eventHandler);

	this->closeGame(charset, screen, scrtex, window, renderer);
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) { // change this into a vector to be more efficient (so it can destroy every gameobject)
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(0);
}
