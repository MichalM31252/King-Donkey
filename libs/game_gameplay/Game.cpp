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


void Game::initGame() {

	VisualHandler visualHandler;

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

	visualHandler.setColors(screen);
	

	tick1 = SDL_GetTicks();

	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second

	worldTime = 0; // how long the game is running

	distance = 0; // the distance of the eti sign (this could maybe work for collision detection)
	etiSpeed = 1; // speed of the eti sign

	while (true) { // 1 frame of the game
		tick2 = SDL_GetTicks();
		deltaTime = (tick2 - tick1) * 0.001; // deltaTime is time in miliseconds since the last screen was drawn to make sure that the game runs at the same speed on different computers
		tick1 = tick2;

		worldTime += deltaTime;

		distance += etiSpeed * deltaTime;

		SDL_FillRect(screen, NULL, visualHandler.platformColor);

		// draws the eti.bmp image, for drawing 	                        
		visualHandler.DrawSurface(screen, eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	

		fpsTimer += deltaTime;
		if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
			fps = frames * REFRESH_RATE;
			frames = 0;
			fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		// tekst informacyjny / info text
		visualHandler.DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, visualHandler.blue, visualHandler.black); // draws border around the whole screen
		visualHandler.DrawRectangle(screen, 1, 1, SCREEN_WIDTH - 2, 18, visualHandler.blue, visualHandler.blue);

		// this is here to reserve a space for a long text
		char text[128];
		sprintf(text, "Time: %.1lf s  Score: 00000  Lives: 3", worldTime); //            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		visualHandler.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7, text, charset);


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);



		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)

		frames++;
	};
	this->closeGame(charset, screen, scrtex, window, renderer);
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
