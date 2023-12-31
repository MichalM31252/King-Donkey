#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "Game.h"
	#include "../Constants.h"
}

Game::Game(){
	quit = 0;
}

void Game::initEverything(int *rc, SDL_Window *window, SDL_Renderer *renderer) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // check if sdl works
		printf("SDL_Init error: %s\n", SDL_GetError());
		this->closeGame();
	}

	*rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer); // create window and renderer
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		this->closeGame();
	};

}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) {
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(0);
}
